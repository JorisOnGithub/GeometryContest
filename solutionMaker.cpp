//
// Created by joris on 4/25/19.
//

#include "solutionMaker.h"

/*
void solutionMaker::createSolution() {
    std::vector<lineseg> edges{};


    for (int i = 0; i < triangles.size(); i++) {
        std::vector<lineseg> triangleEdges = triangles.at(i).getEdges();

        for (int j = 0; j < triangleEdges.size(); j++) {
            if (std::find(edges.begin(), edges.end(), triangleEdges.at(j)) != edges.end()) {
                std::vector<lineseg> newedges{};

                for (int k = 0; k < edges.size(); k++) {
                    if (!(triangleEdges.at(j) == edges.at(k))) {
                        newedges.emplace_back(edges.at(k));
                    }
                }

                edges = newedges;
            } else {
                edges.emplace_back(triangleEdges.at(j));
            }
        }
    }

    std::cout << edges.size() << std::endl;
    std::vector<vec> points{};

    for (int i = 0; i < edges.size(); i++) {
        lineseg seg = edges.at(i);
        points.emplace_back(seg.a);
        points.emplace_back(seg.b);
    }

    this->solution = polygon();
    this->solution.setPoints(points);
}
*/

void solutionMaker::realSolution() {
    // set of points that are not yet in the solution polygon
    std::set<vec> available;
    for (int i = 0; i < this->points.size(); i++) {
        available.insert(this->points[i]);
    }

    // quadtree to maintain the edges of the current polygon
    vec bl(0, 0);
    vec tr(1000000000, 1000000000);
    quadtree qt(&bl, &tr);

    // first point in polygon is an arbitrary point
    vec start = *available.begin();
    available.erase(start);

    // create first linked list point
    llPoint first = llPoint(start);
    llPoint *cur = &first;

    // get closest point to starting point (for small area)
    vec second = getClosestPoint(cur->point, available);

    // create linked list node for second point
    insertAt(*cur, second);
    // remove second point from available points
    available.erase(second);

    // create first edge between the first two points
    vec *a = &cur->point;
    vec *b = &cur->next->point;
    lineseg ls(a, b);
    cur->edge = &ls;

    // insert edge into quadTree
    if (!qt.insert(ls)) throw "insert failed";
//    inPoly.insert(&ls);

    // number to create debugging visualizations
//    int fileCount = 0;

    // limit to prevent timeouts UNSET FOR LARGE INPUTS
    int totalLimit = 1000000;

    // this boolean makes sure that the first point to be added is handled differently:
    // when turning a line into a triangle the edge of the line should stay in the polygon
    bool isStart = true;

    lineseg *ls1; // first of two linesegments to add after adding a point to the polygon
    lineseg *ls2;

    // keep adding vertices until polygon contains all points
    while (!available.empty()) {
        if (cur->next == NULL) throw "this point should have a next point";

        // loop over all potential points to add
        auto it = available.begin();
        for (; !available.empty() && it != available.end(); it++) {
            // deal with timeouts
            totalLimit--;
            if (totalLimit <= 0) {
                available.clear();
                std::cout << "solutionMaker timed out" << std::endl;
            }

            // if all points are in the polygon, stop looking for points
            if (available.empty()) {
                break;
            }

            // keep track if the current point can be added to the polygon or not (at the current edge)
            bool isPossible = true;
            vec p = *it;

            // check if when we add this point to the polygon, another point gets inside the polygon
            if (newTriangleContainsPoint(*cur, p)) {
                isPossible = false;
            }
            // point p cannot be added to the current edge, look for another point
            if (!isPossible) continue;

            // check if the newly created line segments (by adding point p) intersect with any other line segments in the polygon
            ls1 = new lineseg(&cur->point, &p);
            ls2 = new lineseg(&p, &cur->next->point);
            if (qt.intersects_line(*ls1) || qt.intersects_line(*ls2)) {
                isPossible = false;
            }

            // add removed edge back when we don't take this new point
            if (!isPossible) {
                continue;
            }

            /// We are adding this point to the polygon at this edge

            // this edge is replaced by two new edges (except for the first new point going from a line to a triangle)
            if (!isStart && !qt.remove(*cur->edge)) throw "remove failed";

            // we can add this point to the polygon
            it = available.erase(it);

            // add new point to the linked list
            llPoint* newPoint = insertAt(*cur, p);

            // recreate the line segments that we want to add
            delete (ls1);
            delete (ls2);
            ls1 = new lineseg(&cur->point, &p);
            ls2 = new lineseg(&p, &cur->next->next->point);

            // add new line segments to the quad tree
            if (!qt.insert(*ls1)) throw "insert failed";
            if (!qt.insert(*ls2)) throw "insert failed";

            // update the linked list
            cur->edge = ls1;
            newPoint->edge = ls2;
            isStart = false;

            /*
            // This code visualizes the new polygon and saves it as ipe file
            std::vector<vec> tempSol = getPointList(first);
            std::cout << "visualizing inbetween" << std::endl;
            visualiser v;
            try {
                v.visualise(this->points, tempSol, "testing"+std::to_string(fileCount++));
            } catch (const char *e) {
                std::cerr << e << std::endl;
            }
             */

            // solution found
            if (available.empty()) break;
        }

        if (available.empty()) break;

        // being here means we cannot add a point to this edge
        // move to the next edge (point that has a next point)
        if (cur->next->next != NULL) {
            cur = cur->next;
        } else {
            cur = &first;
        }
    }

    // set solution
    std::vector<vec> result = getPointList(first);
    this->solution = result;
}


vec solutionMaker::getClosestPoint(const vec &p, const std::set<vec> &available) const {
    if (available.empty()) throw "available is empty";
    double minDist = std::numeric_limits<int>::max(); // point coordinates cannot get higher than this
    vec result;

    // try out all points available
    for (auto i : available) {
        // distance between two points
        double dist = (p - i).norm();
        if (dist < minDist) {
            minDist = dist;
            result = i;
        }
    }

    return result;
}

bool solutionMaker::newTriangleContainsPoint(const llPoint &cur, const vec &p) const {
    // create triangle with the 2 endpoints of the current edge and the new point (p)
    std::vector<vec> pts{};
    pts.emplace_back(p);
    pts.emplace_back(cur.point);
    pts.emplace_back(cur.next->point);
    polygon triangle;
    triangle.setPoints(pts);

    // TODO: optimize!
    // check if this triangle contains a point
    for (vec otherPoint : this->points) {
        // dont compare with points that are part of the triangle, as they are allowed to be in the triangle
        if (otherPoint == p || otherPoint == cur.point || otherPoint == cur.next->point) continue;

        // there is a point in the triangle
        if (triangle.contains(otherPoint)) {
            return true;
        }
    }

    // there are no points in the triangle
    return false;
}

llPoint* insertAt(llPoint &cur, const vec &p) {
    // TODO: does this create a memleak?
    // create new linked list node
    llPoint *newPoint = new llPoint(p);
    // connect new point to next and prev
    newPoint->prev = &cur;
    newPoint->next = cur.next;
    // connect next and prev to new point
    if (newPoint->next != NULL) newPoint->next->prev = newPoint;
    cur.next = newPoint;

    return newPoint;
}

polygon solutionMaker::getSolution() {
    // we do not have a solution yet
    if (this->solution.getPoints().size() == 0) {
        this->realSolution();
    }
    return this->solution;
}

std::vector<vec> solutionMaker::getPointList(llPoint &first) {
    std::vector<vec> result{};
    llPoint *cur = &first;
    while (cur != NULL) {
        result.emplace_back(cur->point);
        cur = cur->next;
    }
    result.emplace_back(first.point);
    return result;
}

// DEBUGGING TOOLS

void solutionMaker::printCurPoly(std::set<lineseg *> curPoly) {
    std::cout << "LINE SEGMENTS CURRENTLY IN POLY:" << std::endl;
    for (auto seg: curPoly) {
        std::cout << seg->toString() << std::endl;
    }
}

void solutionMaker::printList(const llPoint &p) {
    std::cout << " - " << &p << " - ";
    std::cout.flush();
    if (p.next != NULL) printList(*p.next);
}
