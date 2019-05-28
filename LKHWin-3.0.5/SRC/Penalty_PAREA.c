#include "LKH.h"
#include "Segment.h"
#include "dict.h"
#include "pr_tree.h"
//#include "Penalty_PAREA.h"
Node* potential_intersects[4] = { NULL };


/*
 * Penalty function that penalizes crossings. Current penality is #crossings.
 * TODO: efficient line segment intersection, current algorithm is naive O(n^2)
 */
GainType Penalty_PAREA()
{
	//RatTest();
	Node* First = &NodeSet[1], * N1 = First, * N2;
	int P = 0,i=0;
	//intersectionResult SweeplineIntersections = compute_intersections();
	/*if (!TourIsClockwise()) {
		return 2*(long long) Dimension*Dimension;
	}*/
	//memset(Intersect_list, 0, sizeof Intersect_list);
	//dict_test();
	//Node* Intersect_list[5][4]; //= { NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };//
	//puts("Penalty start");
	/* Tour layout is a follows: True node 1 -> copy of 1 -> true node2 -> ...
	So, we test edges ( n1 , S(S(n1) ), (n2, S(S(n2))
	*/
//*/
	//puts("TOUR_CHECK END");//*
	intersectionResult SweeplineIntersections;
	if (UseSweepline) {
		SweeplineIntersections = compute_intersections();
		P = SweeplineIntersections.NumberOfIntersections;
	}
	else {
		do {
			N2 = SUCC(SUCC(N1));//We could skip first suc of N1, as that can't properly intersect, but then we have to be careful to not skip First!
			//N2 = N2->Suc->Suc;
			do {
				//sprintf("Nodes N1: %d and N2: %d", N1->Id, N2->Id);
				//int p = N1->Id;
				//int q = N2->Id;
				//char str[100];
				/*sprintf(str,"Node N1: %d; ", N1->Id);
				puts(str);
				sprintf(str, "Node N1S: %d; ", SUCC(N1)->Id);
				puts(str);
				sprintf(str,"Node N2: %d; ", N2->Id);
				puts(str);
				sprintf(str, "Node N2S: %d; ", SUCC(N2)->Id);
				puts(str);*/
				if (N1 != N2 && SUCC(SUCC(N1)) != SUCC(SUCC(N2)) && SUCC(SUCC(N2)) != N1 && SUCC(SUCC(N1)) != N2 && SegmentsIntersect(N1, SUCC(SUCC(N1)), N2, SUCC(SUCC(N2)))) {//Intersection found
					//printf("=- Intersection at (N%d,N%d) - (N%d,N%d)\n", N1->Id, SUCC(SUCC(N1))->Id, N2->Id, SUCC(SUCC(N2))->Id);
					if (P == 0) {
						potential_intersects[0] = N1;
						potential_intersects[1] = SUCC(SUCC(N1));
						potential_intersects[2] = N2;
						potential_intersects[3] = SUCC(SUCC(N2));
					}
					P++;
					//printf("Intersection at (N%d, N%d) - (N%d, N%d)\n", N1->Id, SUCC(SUCC(N1))->Id, N2->Id, SUCC(SUCC(N2))->Id);
					//printf("Intersection at ([%f,%f], [%f,%f]) - ([%f,%f], [%f,%f])\n", N1->X,N1->Y, SUCC(SUCC(N1))->X, SUCC(SUCC(N1))->Y, N2->X,N2->Y, SUCC(SUCC(N2))->X, SUCC(SUCC(N2))->Y);
					//printTourDEBUG();
					//printf("IDs: %d %d %d %d %d", N1->Id, N1->Suc->Id, N1->Suc->Suc->Id, N1->Suc->Suc->Suc->Id, N1->Suc->Suc->Suc->Suc->Id);
					//printf("IDs: %d %d %d %d %d", N2->Id, N2->Suc->Id, N2->Suc->Suc->Id, N2->Suc->Suc->Suc->Id, N2->Suc->Suc->Suc->Suc->Id);
				}
				/*i++;
				if (i >= 100000) {
					puts("LOOP");
				}*/
			} while ((N2 = SUCC(SUCC(N2))) != First);
		} while ((N1 = SUCC(SUCC(N1))) != First);//*/
	}
	//printf("Penalty ends at %d", P);
	/*if (P <= 5) {
		printf() 
		for (int j = 0; j < P; j++) {
			N1 = Intersect_list[j];
			N2 = Intersect_list[j + 5];
			printf("Intersection at (N%d, N%d) - (N%d, N%d)\n", N1->Id, SUCC(SUCC(N1))->Id, N2->Id, SUCC(SUCC(N2))->Id);
		}
	}*/
	/*if (0 && P == 1) {
		printff("Intersection at (N%d, N%d) - (N%d, N%d)\n", potential_intersects[0]->Id, potential_intersects[1]->Id, potential_intersects[2]->Id, potential_intersects[3]->Id);
		printff("Intersection at ([%f,%f], [%f,%f]) - ([%f,%f], [%f,%f])\n", potential_intersects[0]->X, potential_intersects[0]->Y, potential_intersects[1]->X, potential_intersects[1]->Y, potential_intersects[2]->X, potential_intersects[2]->Y, potential_intersects[3]->X, potential_intersects[3]->Y);
	}*/
	//printTourDEBUG();
	/*if ((SweeplineIntersections.NumberOfIntersections == 0 && P != 0) || (SweeplineIntersections.NumberOfIntersections != 0 && P == 0)) {
		printf("WARNING: Intersection mismatch");
	}*/

	if (P == 0) {
		return 0;
	}
	if (P == 1) {//Compute weight of intersection, should be < Dimension
		Node* intersectionSegment1;
		Node* intersectionSegment2;
		if (UseSweepline) {
			intersectionSegment1 = SweeplineIntersections.S1;
			intersectionSegment2 = SweeplineIntersections.S2;
		}
		else {
			intersectionSegment1 = potential_intersects[0];
			intersectionSegment2 = potential_intersects[2];
		}
		int depth = intersectionWeight(intersectionSegment1, intersectionSegment2);
		//printff("Intersection of depth %d at (N%d, N%d) - (N%d, N%d)\n", depth, potential_intersects[0]->Id, potential_intersects[1]->Id, potential_intersects[2]->Id, potential_intersects[3]->Id);
		return 1 + (long long) depth;
	}
	return P + (long long) Dimension;
}
/*
int dict_test() {
	dict* dct = NULL;
	char str[5];
	dct = pr_dict_new((dict_compare_func) strcmp);
	for (int i = 0; i < 10; i++) {
		sprintf(str, " &d ", 3 * i);
		dict_insert_result res= dict_insert(dct, &i);
		*res.datum_ptr = str;
	}
	int j = 5;
	//int* pt1 = &j;
	void** search1 = dict_search(dct, &j);
	if (search1)
		printf("is %d %s", j, *(char**)search1);
	j = 6;
	void** search2 = dict_search(dct, &j);
	if (search2)
		printf("is %d %s", j, *(char**)search2);
	return 0;
}
/*
dict_compare_func difference(int a, int b) {
	return a - b;
}*/

/*
 * Whether the tour is clockwise. This is the prefered direction for MaxAREA, Counter clockwise is required for MinAREA
 */
int TourIsClockwise() {
	Node* CH = &NodeSet[1];
	while (!CH->OnConvexHull) { CH = SUCC(SUCC(CH)); }
	return !NodeLeftOfOrientedEdge(SUCC(SUCC(CH)), PREDD(PREDD(CH)), CH);
}

/*
 * Given (N1,S(N1)) and (N2,S(N2)) form the only intersection, compute the length of the subpath of the tour that has the wrong direction.
 */
int intersectionWeight(Node* N1, Node* N2) {
	//First, test whether the direction is ok.
	//Node* CH = &NodeSet[1];
	//while (!CH->OnConvexHull) { CH = SUCC(SUCC(CH)); }//Current input should enforce that the first node is on the CH, this is a double check
	Node* N=SUCC(SUCC(N1));
	//int direction_ok = !NodeLeftOfOrientedEdge(SUCC(SUCC(CH)), PREDD(PREDD(CH)), CH);

	//if (!direction_ok)
	//	printf("N%d is on CH, dir is not ok", CH->Id);
	int direction_ok = 1;
	//First, try to reach N2 from N1
	int encountered_CH = 0,path_length=0;
	do {
		if ( !encountered_CH && N->OnConvexHull) { //First CH vertex encounter
			encountered_CH = 1;
			if (direction_ok) {//Direction of tour is OK, so we need the other subpath
				break;
			}
			//Otherwise, the current subpath must be flipped
		}
		path_length++;
	} while ((N = SUCC(SUCC(N))) != N2);
	if ( (direction_ok && !encountered_CH) || (!direction_ok && encountered_CH)) {//If we have not encountered a CH vertex or we did and the tour had the wrong direction, this path must be flipped
		return path_length;
	}
	//Otherwise, N1 from N2 must be flipped
	path_length = 0;
	N = SUCC(SUCC(N2));
	do {
		path_length++;
	} while ((N = SUCC(SUCC(N))) != N1);
	return path_length;
}

int printTourDEBUG() {
	puts("TOUR_CHECK START\n");
	printf("Dim %d; Saved %d", Dimension, DimensionSaved);
	for (int i = 1; i <= Dimension; i++) {
		printf("Node #%d\n", NodeSet[i].Id);
		printf("Coords: X %f; Y %f", NodeSet[i].X, NodeSet[i].Y);
		printf("Suc: %d; Pred: %d\n", NodeSet[i].Suc->Id, NodeSet[i].Pred->Id);
		printf("SUC: %d; PRED: %d\n", SUC(&NodeSet[i])->Id, PRED(&NodeSet[i])->Id);
		printf("SUCC: %d; PREDD: %d\n", SUCC(&NodeSet[i])->Id, PREDD(&NodeSet[i])->Id);
	}
	return 1;
}

/*
 * Wether the segments (a1,a2) and (b1,b2) intersect.
 */
int SegmentsIntersect(Node* a1, Node* a2, Node* b1, Node* b2)
{
	return SegmentIntersectsLine(a1, a2, b1, b2) && SegmentIntersectsLine(b1, b2, a1, a2);
}

/*
 * Whether the segment (a1,a2) intersects the line through (b1,b2)
 */
int SegmentIntersectsLine(Node* a1, Node* a2, Node* b1, Node* b2)
{
	return (!NodeLeftOfOrientedEdge(a1, b1, b2) && !NodeLeftOfOrientedEdge(a2, b2, b1)) //a1 right or on (b1,b2) and a2 left or on (b1,b2)
		|| (!NodeLeftOfOrientedEdge(a2, b1, b2) && !NodeLeftOfOrientedEdge(a1, b2, b1));//a2 right or on (b1,b2) and a1 left or on (b1,b2)
}

/*
 * Whether node Nc lies strictly to the left of the ray from Norigin to Ndir
 */
int NodeLeftOfOrientedEdge(Node* Nc, Node* Norigin, Node* Ndir)
{
	if (Norigin->X == Ndir->X) {//Vertical line
		return (Norigin->Y < Ndir->Y && Nc->X < Norigin->X) || (Norigin->Y > Ndir->Y && Nc->X > Norigin->X);
	}
	double slope,intercept;
	slope = (Norigin->Y - Ndir->Y) / (Norigin->X - Ndir->X);
	intercept = Norigin->Y - slope * Norigin->X;
	return (Norigin->X < Ndir->X && Nc->Y > slope * Nc->X + intercept) //Ray to the right, left is above ray
		|| (Norigin->X > Ndir->X && Nc->Y < slope * Nc->X + intercept);//Ray to the left, left is below ray
}

/*GainType Penalty_EXAMPLE()
{
	Node* First = &NodeSet[1], * N = First;
	int P, i = 1, j;
	Constraint* ConPred = 0, * ConSuc = 0;
	static Constraint* Con = 0;

	if (SUCC(First)->Id != First->Id + DimensionSaved) {
		do
			if (N->Id <= DimensionSaved)
				N->Loc = i++;
		while ((N = SUCC(N)) != First);
	}
	else {
		do
			if (N->Id <= DimensionSaved)
				N->Loc = i++;
		while ((N = PREDD(N)) != First);
	}
	P = DimensionSaved - NodeSet[DimensionSaved].Loc;
	if (P > CurrentPenalty || (P == CurrentPenalty && CurrentGain <= 0))
		return CurrentPenalty + (CurrentGain > 0);
	if (CurrentPenalty == 0) {
		if (Con && Con->t1->Loc > Con->t2->Loc)
			return 1;
		for (i = Swaps - 1; i >= 0; i--) {
			for (j = 1; j <= 4; j++) {
				N = j == 1 ? SwapStack[i].t1 :
					j == 2 ? SwapStack[i].t2 :
					j == 3 ? SwapStack[i].t3 : SwapStack[i].t4;
				if (N->Id <= DimensionSaved) {
					for (Con = N->FirstConstraint; Con; Con = Con->Next)
						if (Con->t1->Loc > Con->t2->Loc)
							return 1;
				}
			}
		}
	}
	for (Con = FirstConstraint; Con; ConPred = Con, Con = ConSuc) {
		ConSuc = Con->Suc;
		if (Con->t1->Loc > Con->t2->Loc) {
			if (Con != FirstConstraint) {
				ConPred->Suc = ConSuc;
				Con->Suc = FirstConstraint;
				FirstConstraint = Con;
				Con = ConPred;
			}
			if (++P > CurrentPenalty ||
				(P == CurrentPenalty && CurrentGain <= 0))
				return CurrentPenalty + (CurrentGain > 0);
		}
	}
	return P;
}
*/