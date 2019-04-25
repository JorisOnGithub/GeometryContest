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
    lineseg* edge; // edge to next point
    llPoint *prev;

    llPoint(vec &p) {
        point = p;
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
        points.emplace_back(*seg.a);
        points.emplace_back(*seg.b);
    }

    this->solution = polygon();
    this->solution.setPoints(points);
}

void solutionMaker::realSolution() {
    // set of all points that are already in the solution
    std::set<vec> available;
    for (int i = 0; i < this->points.size(); i++) {
        available.insert(this->points[i]);
    }

    // quadtree to maintain the edges of the current polygon
    quadtree qt(vec(0,0), vec(1000000000, 1000000000));

    // start points to linked list with points
    vec start = *available.begin();
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
    vec* a = &cur->point;
    vec* b = &cur->next->point;
    lineseg ls(a,b);
    qt.insert(&ls);
    cur->edge = &ls;

    // keep adding vertices until polygon contains all points
    while (!available.empty()) {
        if (cur->next == NULL) throw "this point should have a next point";

        // loop over all potential points to add
        for (auto i = available.begin(); i != available.end(); i++) {
            bool isPossible = true;
            vec p = *i;

            // create triangle
            std::vector<vec> pts {};
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
            lineseg ls1 = lineseg(&p, &cur->point);
            lineseg ls2 = lineseg(&p, &cur->point);
            if (qt.intersects_line(&ls1) || qt.intersects_line(&ls2)) {
                isPossible = false;
            }
            if (!isPossible) continue;

            // we can add this point to the polygon

            // remove old linesegment between cur and cur->next
            qt.remove(cur->edge);

            // add new point to the linked list
            llPoint newPoint(p);
            newPoint.prev = cur;
            newPoint.next = cur->next;
            newPoint.next->prev = &newPoint;
            cur->next = &newPoint;

            // add new line segments to the quad tree
            lineseg l1(&cur->point, &p);
            lineseg l2(&p, &newPoint.next->point);
            qt.insert(&l1);
            qt.insert(&l2);
            cur->edge = &l1;
            newPoint.edge = &l2;
        }

        // being here means we cannot add a point to this edge
        // move to the next edge
        if (cur->next->next != NULL) {
            cur = cur->next;
        } else {
            cur = &first;
        }
    }
    // first points to a linked list containing the polygon
    std::vector<vec> result{};
    cur = &first;
    while (cur != NULL) {
        result.emplace_back(cur->point);
        cur = cur->next;
    }

    this->solution = result;
}

polygon solutionMaker::getSolution() {
    // we do not have a solution yet
    if (this->solution.getPoints().size() == 0) {
        this->createSolution();
    }
    return this->solution;
}
