//
// Created by joris on 4/25/19.
//

#include <limits>
#include "solutionMaker.h"
#include "datastructures/lineseg.h"
#include "datastructures/quadtree.h"
#include <set>
#include <algorithm>
#include <iostream>

struct llPoint {
    vec point;
    llPoint *next;
    lineseg *edge; // edge to next point
    llPoint *prev;

    llPoint(vec &p) {
        point = p;
        next = NULL;
        prev = NULL;
    }
};

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

std::vector<vec> getPointList(llPoint &first) {
    std::vector<vec> result{};
    llPoint *cur = &first;
    while (cur != NULL) {
        result.emplace_back(cur->point);
        cur = cur->next;
    }
    result.emplace_back(first.point);
    return result;
}

void printCurPoly(std::set<lineseg*> curPoly) {
    std::cout << "LINE SEGMENTS CURRENTLY IN POLY:" << std::endl;
    for (auto seg: curPoly) {
        std::cout << seg->toString() << std::endl;
    }
}

void printList(const llPoint &p) {
    std::cout << " - " << &p << " - ";
    std::cout.flush();
    if (p.next != NULL) printList(*p.next);
}

void solutionMaker::realSolution() {
    // set of all points that are already in the solution
    std::set<vec> available;
    for (int i = 0; i < this->points.size(); i++) {
        available.insert(this->points[i]);
    }
    // set of linesegments currently in the polygon, used for debugging
    std::set<lineseg*> inPoly;

    // quadtree to maintain the edges of the current polygon
    vec bl(0, 0);
    vec tr(1000000000, 1000000000);
    quadtree qt(&bl, &tr);

    // start points to linked list with points
    vec start = *available.begin();
    // TODO: this does not work, look at my code for example how to use iterator with removing
    available.erase(start);

    llPoint first = llPoint(start);
    llPoint *cur = &first;

    // start with shortest edge from starting point
    double minDist = std::numeric_limits<int>::max();
    vec second;
    for (auto i : available) {
        // distance between two points
        double dist = (cur->point - i).norm();
        if (dist < minDist) {
            minDist = dist;
            second = i;
        }
    }
    llPoint second_ll(second);
    cur->next = &second_ll;
    second_ll.prev = cur;

    // insert first edge into quad tree
    vec *a = &cur->point;
    vec *b = &cur->next->point;
    lineseg ls(a, b);

    if (!qt.insert(ls)) throw "insert failed";
    inPoly.insert(&ls);
    cur->edge = &ls;

    int fileCount = 0;
    int totalLimit = 2000;

    // keep adding vertices until polygon contains all points
    while (!available.empty()) {
        if (cur->next == NULL) throw "this point should have a next point";

        auto it = available.begin();
        // loop over all potential points to add
        for (; !available.empty() && it != available.end(); it++) {
            totalLimit--;
            if (totalLimit <= 0) {
                available.clear();
                std::cout << " WE ARE FUCKED BOYYYYYYSSS ";
            }
            if (available.empty()) {
                break;
            }
            bool isPossible = true;
            vec p = *it;

            // create triangle
            std::vector<vec> pts{};
            pts.emplace_back(p);
            pts.emplace_back(cur->point);
            pts.emplace_back(cur->next->point);
            polygon triangle;
            triangle.setPoints(pts);

            // check if this triangle contains a point
            for (vec otherPoint : this->points) {
                // dont compare with points that are part of the triangle
                if (otherPoint == p || otherPoint == cur->point || otherPoint == cur->next->point) continue;

                if (triangle.contains(otherPoint)) {
                    isPossible = false;
                    break;
                }
            }
            if (!isPossible) continue;

            // check if the line segments (cur.target, p) or (cur.twin.target, p) intersect with the current polygon
            lineseg ls1 = lineseg(&cur->point, &p);
            lineseg ls2 = lineseg(&p, &cur->next->point);
            // before checking intersection remove the edge that makes a triangle with ls1 and ls2
            if (!qt.remove(*cur->edge)) {
                throw "remove failed";
            }

            printCurPoly(inPoly);
            std::cout << "old line segment is " << (*cur->edge).toString() << std::endl;
            std::cout << "ls1 is " << ls1.toString() << std::endl;
            std::cout << "ls2 is " << ls2.toString() << std::endl;
            if (qt.intersects_line(ls1) || qt.intersects_line(ls2)) {
                isPossible = false;
            }
            // add removed edge back when we don't take this new point
            if (!isPossible) {
                std::cout << "THEY INTERSECT WITH POLY";
                if (!qt.insert(*cur->edge)) {
                    throw "insert failed";
                }
                inPoly.insert(cur->edge); // DEBUG
                continue;
            }
            std::cout << "THEY DONT INTERSECT WITH POLY";

            // we can add this point to the polygon
            it = available.erase(it);

            // add new point to the linked list
            llPoint *newPoint = new llPoint(p);
            newPoint->prev = cur;
            newPoint->next = cur->next;
            if (newPoint->next != NULL) newPoint->next->prev = newPoint;
            cur->next = newPoint;

            // add new line segments to the quad tree
            if (!qt.insert(ls1)) throw "insert failed";
            if (!qt.insert(ls2)) throw "insert failed";
            inPoly.insert(&ls1); // DEBUG
            inPoly.insert(&ls2); // DEBUG
            cur->edge = &ls1;
            newPoint->edge = &ls2;
            std::vector<vec> tempSol = getPointList(first);

            std::cout << "visualizing inbetween" << std::endl;
            visualiser v;
            try {
                v.visualise(this->points, tempSol, "testing"+std::to_string(fileCount++));
            } catch (const char *e) {
                std::cerr << e << std::endl;
            }

            if (available.empty()) break;
        }

        if (available.empty()) break;
        // being here means we cannot add a point to this edge
        // move to the next edge
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





polygon solutionMaker::getSolution() {
    // we do not have a solution yet
    if (this->solution.getPoints().size() == 0) {
        this->realSolution();
    }
    return this->solution;
}
