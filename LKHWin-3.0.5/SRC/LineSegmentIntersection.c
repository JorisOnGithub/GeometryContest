#include "LKH.h"
#include "Segment.h"
#include "dict.h"
#include "pr_tree.h"

typedef struct eventPoint eventPoint;
typedef struct eventPointsAtCoordinate eventPointsAtCoordinate;
double Y_CoordinateOfSegment(const Node*, const Node*, double);
int sweepline_Intersection_lower(const Node*, const Node*);
int addIntersectionEvent(dict*, Node*, Node*);
void display_status(dict*);
void display_status_consistency(dict*);
void printTourAsExternal(void);
int status_consistent(dict*);
enum event_type {Segment_start=0, Segment_end=1, Segment_intersection=2,empty_event=-1};
double status_percision = 1E-15;
double event_queue_percision = 1E-15;
Rational zeroR = { .Numerator = 0, .Denominator=1};
Rational sweepline_X;

struct eventPoint {
	enum event_type Type;
	Rational X;
	Rational Y;
	Node* FirstSegmentNode;
	Node* SecondSegmentNode;
};


eventPoint empty_event_point = {.Type=empty_event};


struct eventPointsAtCoordinate {
	Rational X;
	int numberOfPoints;
	eventPoint eventPoints[2];
};

static void key_val_free(void* key, void* datum) {
	free(key);
	free(datum);
}

void print_eventPoint(eventPoint* point) {
	switch (point->Type) {
	case Segment_start:
		printf("Start event of node %d\n", point->FirstSegmentNode->Id);
		break;
	case Segment_end:
		printf("End event of node %d\n", point->FirstSegmentNode->Id);
		break;
	case Segment_intersection:
		printf("Intersection event of node %d\n", point->FirstSegmentNode->Id);
		break;
	}
}

void print_PointsAtCoordinate(eventPointsAtCoordinate* points) {
	printf("%d Points at %lld/%lld ~ %f:\n", points->numberOfPoints, points->X.Numerator, points->X.Denominator, RtoDouble(points->X));
	for (int i = 0; i < points->numberOfPoints; i++) {
		print_eventPoint(&points->eventPoints[i]);
	}
}

dict_insert_result event_queue_insert(dict* event_queue, eventPoint p) {
	Rational* stored_key; 
	assert (stored_key = (Rational*) malloc(sizeof * stored_key));
	*stored_key = p.X;
	//Try to insert a new key
	eventPointsAtCoordinate* events_at_coord;
	dict_insert_result res = dict_insert(event_queue, stored_key);
	if (res.inserted) {
		//Create new event point holder
		assert(events_at_coord = malloc(sizeof * events_at_coord));
		events_at_coord->X = p.X;
		//printf("Inserted event at %lld/%lld ~ %f\n", events_at_coord->X.Numerator, events_at_coord->X.Denominator, RtoDouble(events_at_coord->X));
		events_at_coord->numberOfPoints = 0;
		*res.datum_ptr = events_at_coord;
	}
	else {
		events_at_coord = *res.datum_ptr;
		//printf("Retrieved event at %lld/%lld ~ %f\n", events_at_coord->X.Numerator, events_at_coord->X.Denominator, RtoDouble(events_at_coord->X));
	}

	events_at_coord->eventPoints[events_at_coord->numberOfPoints++] = p;
	//print_PointsAtCoordinate(events_at_coord);
	return res;
}

dict_remove_result event_queue_pop(dict* event_queue) {
	//Search for the smallest value (greater than 0) in the queue
	//double* zero_pointer; assert(zero_pointer = malloc(sizeof *zero_pointer));
	//*zero_pointer = 0;
	//double zero = 0;
	void **search = dict_search_ge(event_queue, &zeroR);
	//free(zero_pointer);
	//eventPointsAtCoordinate result;
	if (search) {
		//void ** result = *(eventPointsAtCoordinate **)search;
		//double* delete_key; assert(delete_key = malloc(sizeof *delete_key));
		Rational delete_key = (*(eventPointsAtCoordinate**)search)->X;
		dict_remove_result remove_res = dict_remove(event_queue, &delete_key);
		//free(delete_key);
		if (remove_res.removed) {
			Rational removed_key = *(Rational*)remove_res.key;
			//printf("del key: %lld/%lld; rem key: %lld/%lld\n ", delete_key.Numerator, delete_key.Denominator, removed_key.Numerator, removed_key.Denominator);
			//printf("removed '%f' from event queue\n", RtoDouble(*((Rational*) remove_res.key)));
			//free(remove_res.key);
			//free(remove_res.datum);
		}
		else {
			printf("WARNING: key '%f' not in event queue!\n", RtoDouble(delete_key));
		}
		return remove_res;
	}
	//printf("lowest point not found\n");
	dict_remove_result empty_result;
	empty_result.removed = 0;
	return empty_result;
}

/*
 * Compares two x-coordinates. 0 if equal, -1 of x1<x2, 1 if x1>x2
 */
int xcoord_smaller(const Rational* x1, const Rational* x2) {
	//printf("x1: %lld/%lld ~ %f; x2: %lld/%lld ~ %f\n", x1->Numerator, x1->Denominator, RtoDouble(*x1),
	//	x2->Numerator, x2->Denominator, RtoDouble(*x2));
	if (RequalsR(*x1, *x2)) {
		return 0;
	}
	if (RstrictlylessR(*x1,*x2)) {
		return -1;
	}
	return 1;
}

Node* largerNode(Node* largeNode, Node* newNode) {
	if (largeNode == NULL || sweepline_Intersection_lower(largeNode, newNode) < 0) {
		return newNode;
	}
	return largeNode;
}

Node* smallerNode(Node* smallNode, Node* newNode) {
	if (smallNode == NULL || sweepline_Intersection_lower(newNode, smallNode) < 0) {
		return newNode;
	}
	return smallNode;
}

intersectionResult compute_intersections() {
	sweepline_X = RfromI(0);
	intersectionResult intersectionResult;
	intersectionResult.NumberOfIntersections = 0;
	//First, initialise the segment start and end events

	//The event queue has (a pointer to) the x-coordinate as key. Each key is associated with a (possibly empty) eventpoint for each event_type.
	//For now, assume all points involved have an unique x-coordinate.
	dict *event_queue = rb_dict_new((dict_compare_func)xcoord_smaller);
	Node *First = &NodeSet[1], *N = First;
	int insert_cycle = 0;
	do {
		Node* N2 = SUCC(SUCC(N));
		//printf("Insert #%d\n", insert_cycle++);
		//printf("Segment (%d,%d)\n\n", N->Id, N2->Id);
		//Create a start and end event for this segment

		int N_left = N->X < N2->X;

		eventPoint start, end;		
		start.Type = Segment_start;
		start.X = RfromI(N_left ? N->X : N2->X);
		start.Y = RfromI(N_left ? N->Y : N2->Y);
		start.FirstSegmentNode = N;
		//printf("Start X %lld/%lld, Y: %lld/%lld\n", start.X.Numerator, start.X.Denominator, start.Y.Numerator, start.Y.Denominator);

		end.Type = Segment_end;
		end.X = RfromI(N_left ? N2->X : N->X);
		end.Y = RfromI(N_left ? N2->Y : N->Y);
		end.FirstSegmentNode = N;
		//printf("End X %lld/%lld, Y: %lld/%lld\n", end.X.Numerator, end.X.Denominator, end.Y.Numerator, end.Y.Denominator);

		//insert the events in the queue
		event_queue_insert(event_queue, start);	
		event_queue_insert(event_queue, end);

	} while ((N = SUCC(SUCC(N))) != First);

	dict* status = rb_dict_new((dict_compare_func) sweepline_Intersection_lower);


	dict_remove_result result = event_queue_pop(event_queue);
	int iteration_limiter = 0;
	while (result.removed) { //&& iteration_limiter<100) {
		eventPointsAtCoordinate* current_events = result.datum;
		//Do not update sweepline now, but _after_ deletion
		//print_PointsAtCoordinate(current_events);
		//sort event points by type. Assume there are at most 2 of each type.
		int NumStartEvents = 0, NumEndEvents = 0, NumIntersectionEvents = 0;
		eventPoint startEvents[2], endEvents[2], intersectionEvents[2];
		for (int i = 0; i < current_events->numberOfPoints; i++) {
			eventPoint current_event = current_events->eventPoints[i];
			switch (current_event.Type) {
			case Segment_start:
				startEvents[NumStartEvents++] = current_event;
				break;
			case Segment_end:
				endEvents[NumEndEvents++] = current_event;
				break;
			case Segment_intersection:
				intersectionEvents[NumIntersectionEvents++] = current_event;
				break;
			case empty_event:
				printf("WARNING: Empty event in event queue\n");
				break;
			}
		}
		if (NumIntersectionEvents > 0 && NumEndEvents + NumStartEvents > 0) {
			printf("WARNING: Intersection event coincides with start/end events");
		}

		if (NumIntersectionEvents > 0) {
			for (int i = 0; i < NumIntersectionEvents; i++) {
				Node* N1 = intersectionEvents[i].FirstSegmentNode;
				Node* N2 = intersectionEvents[i].SecondSegmentNode;
				intersectionResult.NumberOfIntersections++;
				intersectionResult.S1 = N1;
				intersectionResult.S2 = N2;
				printf("== Intersection at (N%d,N%d) - (N%d,N%d)\n", N1->Id, SUCC(SUCC(N1))->Id, N2->Id, SUCC(SUCC(N2))->Id);
			}
		}
		//'intersections' among start and end events are not relevant, so lets ignore them for now. 
		//This is fine under the assumption that an event points cannot both intersection and start/end events.

		//First, handle the events scheduled for deletion. If there are no insertions, remember the 'boundary' of the segments to delete.
		int insertion_exists = NumStartEvents + NumIntersectionEvents > 0;
		Node* upper_boundary = NULL;
		Node* lower_boundary = NULL;

		// REMOVAL: remove intersection and end segments, keep track of boundary if there are no insertions
		for (int i = 0; i < NumEndEvents; i++) {
			eventPoint end_event = endEvents[i];
			if (!insertion_exists) {
				upper_boundary = largerNode(upper_boundary, end_event.FirstSegmentNode);
				lower_boundary = smallerNode(lower_boundary, end_event.FirstSegmentNode);
			}
			dict_remove_result remove_res = dict_remove(status, end_event.FirstSegmentNode);
			if (!remove_res.removed) {
				display_status(status);
				printf("WARNING: Cannot remove end segment (N%d, N%d)\n", end_event.FirstSegmentNode->Id, SUCC(SUCC(end_event.FirstSegmentNode))->Id);
				void** searchi = dict_search(status, end_event.FirstSegmentNode);
				if (searchi) {
					printf("WARNING: key found in status");
				}
			}
		}
		for (int i = 0; i < NumIntersectionEvents; i++) {
			eventPoint intersection_event = intersectionEvents[i];
			//NB: if there is an intersection event, then there is an insertion, so we do not keep track of the deletions.
			dict_remove_result remove_res = dict_remove(status, intersection_event.FirstSegmentNode);
			if (!remove_res.removed) {
				display_status(status);
				printf("WARNING: Cannot remove intersection segment (N%d, N%d)\n", intersection_event.FirstSegmentNode->Id, SUCC(SUCC(intersection_event.FirstSegmentNode))->Id);
			}
			remove_res = dict_remove(status, intersection_event.SecondSegmentNode);
			if (!remove_res.removed) {
				display_status(status);
				display_status_consistency(status);
				printf("just removed (N%d,N%d)", intersection_event.FirstSegmentNode->Id, SUCC(SUCC(intersection_event.FirstSegmentNode))->Id);
				printf("attempting removal of (N%d,N%d)", intersection_event.SecondSegmentNode->Id, SUCC(SUCC(intersection_event.SecondSegmentNode))->Id);
				printf("WARNING: Cannot remove intersection segment (N%d, N%d)\n", intersection_event.SecondSegmentNode->Id, SUCC(SUCC(intersection_event.SecondSegmentNode))->Id);
			}
		}
		sweepline_X = current_events->X;
		//INSERTION: insert start and intersection events, keeping track of their boundary.
		dict_insert_result insert_res;
		for (int i = 0; i < NumStartEvents; i++) {
			eventPoint start_event = startEvents[i];
			upper_boundary = largerNode(upper_boundary, start_event.FirstSegmentNode);
			lower_boundary = smallerNode(lower_boundary, start_event.FirstSegmentNode);
			insert_res = dict_insert(status, start_event.FirstSegmentNode);
			if (insert_res.inserted) {
				//Searching does not return the key, so we must store the segment in the datum pointer
				*insert_res.datum_ptr = start_event.FirstSegmentNode;
			}
			else {
				display_status(status);
				printf("WARNING: Cannot insert start segment (N%d,N%d)\n", start_event.FirstSegmentNode->Id, SUCC(SUCC(start_event.FirstSegmentNode))->Id);
			}
		}

		for (int i = 0; i < NumIntersectionEvents; i++) {
			eventPoint intersection_event = intersectionEvents[i];
			upper_boundary = largerNode(upper_boundary, intersection_event.FirstSegmentNode);
			lower_boundary = smallerNode(lower_boundary, intersection_event.FirstSegmentNode);
			insert_res = dict_insert(status, intersection_event.FirstSegmentNode);
			if (insert_res.inserted) {
				*insert_res.datum_ptr = intersection_event.FirstSegmentNode;
			}
			else {
				printf("WARNING: Cannot insert start segment (N%d,N%d)\n", intersection_event.FirstSegmentNode->Id, SUCC(SUCC(intersection_event.FirstSegmentNode))->Id);
			}

			upper_boundary = largerNode(upper_boundary, intersection_event.SecondSegmentNode);
			lower_boundary = smallerNode(lower_boundary, intersection_event.SecondSegmentNode);
			insert_res = dict_insert(status, intersection_event.SecondSegmentNode);
			if (insert_res.inserted) {
				*insert_res.datum_ptr = intersection_event.SecondSegmentNode;
			}
			else {
				display_status(status);
				display_status_consistency(status);
				printTourAsExternal();
				printf("WARNING: Cannot insert start segment (N%d,N%d)\n", intersection_event.SecondSegmentNode->Id, SUCC(SUCC(intersection_event.SecondSegmentNode))->Id);
			}
		}

		//SEARCH: look for new intersection events as a result of new neighbours due to insertion/deletion
		//in case there are no insertions:
		if (!insertion_exists) {
			void** upper_search = dict_search_gt(status, upper_boundary);
			void** lower_search = dict_search_lt(status, lower_boundary);
			//if either of these points does not exist, there are no new intersections to insert.
			if (upper_search && lower_search) {
				int success = addIntersectionEvent(event_queue, *(Node * *)lower_search, *(Node * *)upper_search);
			}
		}
		else {
			//In case of insertions, we check their intersections with the upper and lower boundary in the status
			void** upper_search = dict_search_gt(status, upper_boundary);
			void** lower_search = dict_search_lt(status, lower_boundary);
			if (upper_search) {
				int success = addIntersectionEvent(event_queue, *(Node**)upper_search, upper_boundary);
			}
			if (lower_search) {
				int success = addIntersectionEvent(event_queue, *(Node**)lower_search, lower_boundary);
			}
		}

		//printf("Cycle %d\n", iteration_limiter);
		iteration_limiter++;
		/*if (iteration_limiter >= 99) {
			printf("WARNING: too many iterations");
		}*/
		//print_PointsAtCoordinate(current_events);
		//display_status(status);
		result = event_queue_pop(event_queue);

		//TODO: This check is O(n), remove if you trust that the implementation works.
		//I'm fairly certain that at this point, the implementation is correct if and only if the status remains consistent.
		// (under general position assumptions, at least)
		if (!status_consistent(status)) {
			print_PointsAtCoordinate(current_events);
			printf("Iteration %d\n", iteration_limiter);
			display_status_consistency(status);
			printTourAsExternal();
			printf("WARNING: Inconsistent status\n");
		}
	}

	//TODO: verify free-ing of dicts actually works as intended.
	dict_free(event_queue, key_val_free);
	dict_free(status, key_val_free);
	return intersectionResult;
}

double compute_slope(const Node* N1, const Node* N2) {
	return (N1->Y - N2->Y) / (N1->X - N2->X);
}

double compute_intercept(const Node * N1, const Node * N2) {
	return N1->Y - compute_slope(N1, N2) * N1->X;
}

double Y_CoordinateOfSegment(const Node* Norigin, const Node* Nend, double X) {
	if (Norigin->X == Nend->X) {
		return -1; //this should not happen
	}
	return compute_slope(Norigin, Nend) * X + compute_intercept(Norigin, Nend);
}

/*
 * 0 if segments are equal, <0 if N1 has smaller Y-coord at X of sweepline, >0 if N2 has smaller Y-coord. 
 *   If segments are distinct with equal Y-coord, <0 if N1 has smaller slope
 */
int sweepline_Intersection_lower(const Node* N1, const Node* N2) {
	if (N1->Id == N2->Id) {
		//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, 0);
		return 0;
	}
	Rational Y_intersection1 = RationalSegmentSweepIntersectY(N1, sweepline_X);
	Rational Y_intersection2 = RationalSegmentSweepIntersectY(N2, sweepline_X);
	//printf("Y1: %f, Y2: %f\n", RtoDouble(Y_intersection1), RtoDouble(Y_intersection2));
	if (RequalsR(Y_intersection1, Y_intersection2)) {

		//if intersection with sweepline is at same point, order on slope. This is equivalent to ordering by shifting the sweepline infinitesemaly.
		//const Node* S1_start = N1->X < SUCC(SUCC(N1))->X ? N1 : SUCC(SUCC(N1));
		//const Node* S2_start = N2->X < SUCC(SUCC(N2))->X ? N2 : SUCC(SUCC(N2));
		Rational slope1 = RationalSlope(N1, SUCC(SUCC(N1)));
		Rational slope2 = RationalSlope(N2, SUCC(SUCC(N2)));
		/*if (N1->Id == SUCC(SUCC(N2))->Id || N2->Id == SUCC(SUCC(N1))->Id) {
			if (S1_start->X < sweepline_X) {
				slope1 = -slope1;
			}
			if (S2_start->X < sweepline_X) {
				slope2 = -slope2;
			}
		}*/
		if (RequalsR(slope1, slope2)) {
			printf("WARNING: Y-intersection and slopes are equal, while segments differ\n ");
			//printf("Slope1: %f, Slope2: %f",slope1,slope2);
			//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, 0);
			return 0;
		}
		if (RstrictlylessR(slope1, slope2)) {
			//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, -1);
			return -1;
		}
		//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, 1);
		return 1;
		//return (result < epsilon && -result < epsilon) ? 0 : result;
		/*
		if (N1->Id == SUCC(SUCC(N2))->Id) {
			double result = SUCC(SUCC(N1))->Y - N2->Y;
			return (result < epsilon && -result < epsilon) ? 0 : result;
		}
		if (N2->Id == SUCC(SUCC(N1))->Id) {
			double result = N1->Y - SUCC(SUCC(N2))->Y;
			return (result < epsilon && -result < epsilon) ? 0 : result;
		}
		//In this case, the shared Y coordinate is not at a node, but at an intersection point
		const Node* S1_end = N1->X > SUCC(SUCC(N1))->X ? N1 : SUCC(SUCC(N1));
		const Node* S2_end = N2->X > SUCC(SUCC(N2))->X ? N2 : SUCC(SUCC(N2));
		double result = S1_end->Y - S2_end->Y;
		return (result < epsilon && -result < epsilon) ? 0 : result;
		*/
	}
	if (RstrictlylessR(Y_intersection1, Y_intersection2)) {
		//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, -1);
		return -1;
	}
	//printf("Nodes N1: %d N2: %d val %d\n", N1->Id, N2->Id, 1);
	return 1;
}


/*
 * Whether node Nc lies strictly to the left of the ray from Norigin to Ndir
 */
int NodeLeftOfOrientedEdge2(Node* Nc, Node* Norigin, Node* Ndir)
{
	if (Norigin->X == Ndir->X) {//Vertical line
		return (Norigin->Y < Ndir->Y && Nc->X < Norigin->X) || (Norigin->Y > Ndir->Y && Nc->X > Norigin->X);
	}
	//double slope, intercept;
	double slope = compute_slope(Norigin, Ndir);
	double intercept = compute_intercept(Norigin, Ndir);
	return (Norigin->X < Ndir->X && Nc->Y > slope * Nc->X + intercept) //Ray to the right, left is above ray
		|| (Norigin->X > Ndir->X && Nc->Y < slope * Nc->X + intercept);//Ray to the left, left is below ray
}

/*
 * Whether the segment (a1,a2) intersects the line through (b1,b2)
 */
int SegmentIntersectsLine2(Node* a1, Node* a2, Node* b1, Node* b2)
{
	return (!NodeLeftOfOrientedEdge(a1, b1, b2) && !NodeLeftOfOrientedEdge(a2, b2, b1)) //a1 right or on (b1,b2) and a2 left or on (b1,b2)
		|| (!NodeLeftOfOrientedEdge(a2, b1, b2) && !NodeLeftOfOrientedEdge(a1, b2, b1));//a2 right or on (b1,b2) and a1 left or on (b1,b2)
}

/*
 * Wether the segments (a1,a2) and (b1,b2) intersect.
 */
int SegmentsIntersect2(Node* a1, Node* a2, Node* b1, Node* b2)
{
	return SegmentIntersectsLine(a1, a2, b1, b2) && SegmentIntersectsLine(b1, b2, a1, a2);
}

/*
 * X coordinate of intersection between lines (a1,a2) and (b1,b2), if it exists and is unique.
 */
double IntersectionPointX(Node* a1, Node* a2, Node* b1, Node* b2) {
	return (compute_intercept(b1,b2) - compute_intercept(a1,a2)) / (compute_slope(a1,a2) - compute_slope(b1,b2));
}


int addIntersectionEvent(dict* event_queue, Node* N1, Node* N2) {
	if (N1 != N2 && SUCC(SUCC(N1)) != SUCC(SUCC(N2)) && SUCC(SUCC(N2)) != N1 && SUCC(SUCC(N1)) != N2 && SegmentsIntersect2(N1, SUCC(SUCC(N1)), N2, SUCC(SUCC(N2)))) {
		//intersection found
		eventPoint intersectionEvent;
		intersectionEvent.Type = Segment_intersection;
		intersectionEvent.X = RationalIntersectionPointX(N1, SUCC(SUCC(N1)), N2, SUCC(SUCC(N2)));
		intersectionEvent.Y = RationalSegmentSweepIntersectY(N1, intersectionEvent.X);
		intersectionEvent.FirstSegmentNode = N1;
		intersectionEvent.SecondSegmentNode = N2;
		if (xcoord_smaller(&sweepline_X, &intersectionEvent.X) >= 0) {
			return 0;//intersection is at the current event point or has already been processed.
		}
		void** search_for_X = dict_search(event_queue, &intersectionEvent.X);
		if (search_for_X) {
			//printf("WARNING: Cannot create intersection event of (N%d,N%d) - (N%d,N%d)\n", N1->Id, SUCC(SUCC(N1))->Id, N2->Id, SUCC(SUCC(N2))->Id);
			return 0;//event already exists. This can happen in normal operation.
		}
		dict_insert_result res = event_queue_insert(event_queue, intersectionEvent);
		return 1;
	}
	return 0;//no intersection
}

void display_status(dict* status) {
	dict_itor* itor = dict_itor_new(status);
	dict_itor_first(itor);
	printf("STATUS\n");
	for (; dict_itor_valid(itor); dict_itor_next(itor)) {
		Node* key_node = dict_itor_key(itor);
		Node* datum_node = *dict_itor_datum(itor);
		if (key_node->Id != datum_node->Id) {
			printf("WARNING: key does not match datum in status\n");
			printf("key (N%d,N%d) ", key_node->Id, SUCC(SUCC(key_node))->Id);
			printf("datum (N%d,N%d)\n", datum_node->Id, SUCC(SUCC(datum_node))->Id);
			continue;
		}
		printf("(N%d,N%d)\n", key_node->Id, SUCC(SUCC(key_node))->Id);
	}
	dict_itor_free(itor);
}

void display_status_consistency(dict* status) {
	dict_itor* itor = dict_itor_new(status);
	dict_itor_first(itor);
	Node* previous_key;
	Node* current_key = dict_itor_key(itor);
	dict_itor_next(itor);
	printf("STATUS CONSISTENCY\n");
	for (; dict_itor_valid(itor); dict_itor_next(itor)) {
		previous_key = current_key;
		current_key = dict_itor_key(itor);		
		int difference = sweepline_Intersection_lower(previous_key, current_key);
		char comparison;
		if (difference == 0) {
			comparison = '=';
		}
		else if (difference == -1) {
			comparison = '<';
		}
		else {
			comparison = '>';
		}
		printf("(N%d,N%d) %c (N%d,N%d)\n", previous_key->Id, SUCC(SUCC(previous_key))->Id, comparison, current_key->Id, SUCC(SUCC(current_key))->Id);
	}
	dict_itor_free(itor);
}

int status_consistent(dict* status) {
	dict_itor* itor = dict_itor_new(status);
	dict_itor_first(itor);
	Node* previous_key;
	Node* current_key = dict_itor_key(itor);
	dict_itor_next(itor);
	for (; dict_itor_valid(itor); dict_itor_next(itor)) {
		previous_key = current_key;
		current_key = dict_itor_key(itor);
		int difference = sweepline_Intersection_lower(previous_key, current_key);
		if (difference != -1) {
			printf("Inconsitent status. Expected <0, but got %d\n", difference);
			dict_itor_free(itor);
			return 0;
		}
	}
	dict_itor_free(itor);
	return 1;
}

void printTourAsExternal() {
	puts("TOUR_LIST START\n");
	Node* First = &NodeSet[1], * N = First;
	do {
		printf("%d\n", N->Id - 1);
	} while ((N = SUCC(SUCC(N))) != First);
}
