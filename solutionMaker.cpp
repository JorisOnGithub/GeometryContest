////
//// Created by joris on 4/25/19.
////
//
//#include "solutionMaker.h"
//
//
//void solutionMaker::realSolution(bool visualizeInbetween, bool debug) {
//    // boundaries for quad tree
//    long maxX = this->points[0].x;
//    long maxY = this->points[0].y;
//
//    // set of points that are not yet in the solution polygon
//    std::set<vec> available;
//    for (int i = 0; i < this->points.size() - 1; i++) {
//        maxX = std::max(maxX, (long) this->points[i].x);
//        maxY = std::max(maxY, (long) this->points[i].y);
//        available.insert(this->points[i]);
//    }
//    if (debug) {
//        std::cout << "Made QT with boundaries (" << maxX << "," << maxY << ")" << std::endl;
//    }
//
//    // quadtree to maintain the edges of the current polygon
//    vec bl(0, 0);
//    vec tr(maxX + 5, maxY + 5);
//    quadtree qt(&bl, &tr);
//
//    // get a random first point and make the second point the closest one to the first point
//    // we continue building the polygon from these two points and the edge between them
//    llPoint *first = createStartingEdge(available, qt);
//    llPoint *cur = first;
//
//    // number to create debugging visualizations
//    int fileCount = 0;
//
//    // limit to prevent timeouts UNSET FOR LARGE INPUTS
//    int totalLimit = 1000000000;
//
//    int failCount = 0; // counter to keep track of fails
//
//    // this boolean makes sure that the first point to be added is handled differently:
//    // when turning a line into a triangle the edge of the line should stay in the polygon
//    bool isStart = true;
//
//    lineseg *ls1; // first of two linesegments to add after adding a point to the polygon
//    lineseg *ls2;
//
//    std::set<vec>::iterator it;
//
//    // keep adding vertices until polygon contains all points
//    while (!available.empty()) {
//        if (cur->next == NULL) throw std::runtime_error("this point should have a next point");
//
//        double bestH = 1; // keep track of which point gives best value
//        vec *bestP = NULL; // keep track of best point to add
//
//        // loop over all potential points to add
//        it = available.begin();
//        for (; !available.empty() && it != available.end(); it++) {
//            // deal with timeouts
//            totalLimit--;
//            if (totalLimit <= 0) {
//                available.clear();
//                std::cout << "solutionMaker timed out" << std::endl;
//            }
//
//            // if all points are in the polygon, stop looking for points
//            if (available.empty()) {
//                break;
//            }
//
//            // keep track if the current point can be added to the polygon or not (at the current edge)
//            bool isPossible = true;
//            vec p = *it;
//
//            // check if when we add this point to the polygon, another point gets inside the polygon
//            if (newTriangleContainsPoint(*cur, p)) {
//                isPossible = false;
//            }
//            // point p cannot be added to the current edge, look for another point
//            if (!isPossible) continue;
//
//            // check if the newly created line segments (by adding point p) intersect with any other line segments in the polygon
//            ls1 = new lineseg(&cur->point, &p);
//            ls2 = new lineseg(&p, &cur->next->point);
//            if (qt.intersects_line(*ls1) || qt.intersects_line(*ls2)) {
//                isPossible = false;
//            }
//
//            // free the line segments
//            delete (ls1);
//            delete (ls2);
//
//            // add removed edge back when we don't take this new point
//            if (!isPossible) {
//                continue;
//            }
//
//            /// We are adding this point to the polygon at this edge
//
//            // get heuristic value for adding this point
//            double value = heuristic(cur, p);
//            if (value < bestH) {
//                bestH = value;
//                delete (bestP);
//                bestP = new vec(p.x, p.y);
//            }
//
//            // solution found
//            if (available.empty()) break;
//        }
//
//        // add the best point
//        if (bestP != NULL) {
//            if (debug) {
//                std::cout << "adding " << (this->points.size() - available.size() - 1) << "th best point with value "
//                          << bestH << std::endl;
//
//                // recreate the line segments that we want to add
//                lineseg *ls1 = new lineseg(&cur->point, bestP);
//                lineseg *ls2 = new lineseg(bestP, &cur->next->point);
//
//                // print lines in qt
//                std::set<lineseg> data = qt.get_all_data();
//                std::cout << "data size " << data.size() << std::endl;
//                std::cout << " PRINTING ALL LINE SEGMENTS IN QT " << std::endl;
//                for (auto s: data) {
//                    std::cout << s->toString() << std::endl;
//                }
//                std::cout << "DONE PRINTING" << std::endl;
//
//                std::cout << "NEW LINESEG 1 " << ls1->toString() << std::endl;
//                std::cout << "NEW LINESEG 2 " << ls2->toString() << std::endl;
//
////                delete(ls1);
////                delete(ls2);
//            }
//            addPoint(qt, cur, available, it, *bestP, isStart);
//            delete (bestP);
//
//            // we have added a point, the polygon now has >= 3 points
//            isStart = false;
//
//            // create image if we want to
//            if (visualizeInbetween) {
//                // This code visualizes the new polygon and saves it as ipe file
//                std::vector<vec> tempSol = getPointList(*first);
//                std::cout << "visualizing inbetween" << std::endl;
//                visualiser v;
//                try {
//                    v.visualise(this->points, tempSol, "testing" + std::to_string(fileCount++));
//                } catch (const char *e) {
//                    std::cerr << e << std::endl;
//                }
//            }
//
//            failCount = 0;
//            // keep looking for points
//            continue;
//        }
//
//        if (available.empty()) break;
//
//        failCount++;
//        if (debug) {
//            std::cout << "failCount " << failCount << "Could not find a point to add to this edge, getting new edge"
//                      << std::endl;
//        }
//        if (failCount > this->points.size() * 2) { // infinite loop, abort mission
//            std::cout << "failed too often PRINTING REMAINING POINTS" << std::endl;
//            std::cerr << "DUMPING ALL POINTS NOT IN POLYGON" << std::endl;
//            for (vec v : available) {
//                std::cout << v.toString() << std::endl;
//                std::cerr << v.toString() << std::endl;
//            }
//            break;
//        }
//        // being here means we cannot add a point to this edge
//        // move to the next edge (point that has a next point)
//        if (cur->next->next != NULL) {
//            cur = cur->next;
//        } else {
//            cur = first;
//        }
//    }
//
//    // set solution
//    std::vector<vec> result = getPointList(*first);
//    this->solution = result;
//    if (debug) {
//        std::cerr << "DUMPING FULL POLYGON" << std::endl;
//        for (vec v: result) {
//            std::cerr << v.toString() << std::endl;
//        }
//    }
//
//    // clean linked list
//    delete (first);
//}
//
//
//llPoint *solutionMaker::createStartingEdge(std::set<vec> &available, quadtree &qt) {
//    // first point in polygon is an arbitrary point
//    vec start = *available.begin();
//    available.erase(start);
//
//    // create first linked list point
//    llPoint *first = new llPoint(start);
//    llPoint *cur = first;
//
//    // get closest point to starting point (for small area)
//    vec second = getClosestPoint(cur->point, available);
//
//    // create linked list node for second point
//    insertAt(*cur, second);
//    // remove second point from available points
//    available.erase(second);
//
//    // create first edge between the first two points
//    vec *a = &cur->point;
//    vec *b = &cur->next->point;
//    lineseg *ls = new lineseg(a, b);
//    cur->edge = ls;
//
//    // insert edge into quadTree
//    if (!qt.insert(*ls)) throw std::runtime_error("insert failed 224");
//
//    return cur;
//}
//
//
//void solutionMaker::addPoint(quadtree &qt, llPoint *cur, std::set<vec> &available, std::set<vec>::iterator &it, vec &p,
//                             bool isStart) {
//    /* this edge is replaced by two new edges (except for the first new point going from a line to a triangle) so
//    it needs to be removed */
//    if (!isStart) {
//        if (!qt.remove(*cur->edge)) throw std::runtime_error("remove failed");
//        delete (cur->edge);
//    }
//
//    // we can add this point to the polygon
////    it = available.erase(it);
//    available.erase(p);
//
//    // add new point to the linked list
//    llPoint *newPoint = insertAt(*cur, p);
//
//    // recreate the line segments that we want to add
//    lineseg *ls1 = new lineseg(&cur->point, &newPoint->point);
//    lineseg *ls2 = new lineseg(&newPoint->point, &cur->next->next->point);
//
//    // add new line segments to the quad tree
//    if (!qt.insert(*ls1)) throw std::runtime_error("insert failed 251");
//    if (!qt.insert(*ls2)) throw std::runtime_error("insert failed 252");
//
//    // update the linked list
//    cur->edge = ls1;
//    newPoint->edge = ls2;
//
//}
//
//vec solutionMaker::getClosestPoint(const vec &p, const std::set<vec> &available) const {
//    if (available.empty()) throw std::runtime_error("available is empty");
//    double minDist = std::numeric_limits<int>::max(); // point coordinates cannot get higher than this
//    vec result;
//
//    // try out all points available
//    for (auto i : available) {
//        // distance between two points
//        double dist = (p - i).norm();
//        if (dist < minDist) {
//            minDist = dist;
//            result = i;
//        }
//    }
//
//    return result;
//}
//
//bool solutionMaker::newTriangleContainsPoint(const llPoint &cur, const vec &p) const {
//    // create triangle with the 2 endpoints of the current edge and the new point (p)
//    std::vector<vec> pts{};
//    pts.emplace_back(p);
//    pts.emplace_back(cur.point);
//    pts.emplace_back(cur.next->point);
//    polygon triangle;
//    triangle.setPoints(pts);
//
//    // TODO: optimize!
//    // check if this triangle contains a point
//    for (vec otherPoint : this->points) {
//        // dont compare with points that are part of the triangle, as they are allowed to be in the triangle
//        if (otherPoint == p || otherPoint == cur.point || otherPoint == cur.next->point) continue;
//
//        // there is a point in the triangle
//        if (triangle.contains(otherPoint)) {
//            return true;
//        }
//    }
//
//    // there are no points in the triangle
//    return false;
//}
//
//llPoint *insertAt(llPoint &cur, const vec &p) {
//    // create new linked list node
//    llPoint *newPoint = new llPoint(p);
//    // connect new point to next and prev
//    newPoint->prev = &cur;
//    newPoint->next = cur.next;
//    // connect next and prev to new point
//    if (newPoint->next != NULL) newPoint->next->prev = newPoint;
//    cur.next = newPoint;
//
//    return newPoint;
//}
//
//double solutionMaker::heuristic(llPoint *cur, vec &p) {
//    // create triangle with the 2 endpoints of the current edge and the new point (p)
//    std::vector<vec> pts{};
//    pts.emplace_back(p);
//    pts.emplace_back(cur->point);
//    pts.emplace_back(cur->next->point);
//    polygon triangle;
//    triangle.setPoints(pts);
//    double area = triangle.area();
//
//    // get the linesegments of this point when added
//    lineseg *ls1 = new lineseg(&cur->point, &p);
//    lineseg *ls2 = new lineseg(&p, &cur->next->point);
//    // add the length of both edges
//    double edgeSum = (ls1->a - ls1->b).norm() + (ls2->a - ls2->b).norm();
//
//    // clean the linesegments
//    delete (ls1);
//    delete (ls2);
//
//    // current heuristic formula only looks at area
//    return -1.0 * area + -1.0 * edgeSum * edgeSum;
//}
//
//polygon solutionMaker::getSolution() {
//    // we do not have a solution yet
//    if (this->solution.getPoints().size() == 0) {
//        this->realSolution();
//    }
//    return this->solution;
//}
//
//std::vector<vec> solutionMaker::getPointList(llPoint &first) {
//    std::vector<vec> result{};
//    llPoint *cur = &first;
//    while (cur != NULL) {
//        result.emplace_back(cur->point);
//        cur = cur->next;
//    }
//    result.emplace_back(first.point);
//    return result;
//}
//
//// DEBUGGING TOOLS
//
//void solutionMaker::printCurPoly(std::set<lineseg *> curPoly) {
//    std::cout << "LINE SEGMENTS CURRENTLY IN POLY:" << std::endl;
//    for (auto seg: curPoly) {
//        std::cout << seg->toString() << std::endl;
//    }
//}
//
//void solutionMaker::printList(const llPoint &p) {
//    std::cout << " - " << &p << " - ";
//    std::cout.flush();
//    if (p.next != NULL) printList(*p.next);
//}
//
