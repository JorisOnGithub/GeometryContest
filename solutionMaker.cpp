//
// Created by joris on 4/25/19.
//

#include <limits>
#include "solutionMaker.h"
#include "datastructures/lineseg.h"
#include <set>
#include <algorithm>
#include <iostream>

struct llPoint {
    vec point;
    llPoint* next;
    llPoint* prev;

    llPoint(vec &p) {
        point = p;
    }
};

void solutionMaker::createSolution() {
    std::vector<lineseg> edges{};


    for (int i = 0; i < triangles.size(); i++) {
        std::vector<lineseg> triangleEdges = triangles.at(i).getEdges();

        for (int j = 0; j < triangleEdges.size(); j++)  {
            if (std::find(edges.begin(), edges.end(), triangleEdges.at(j)) != edges.end() ) {
                std::vector<lineseg> newedges {};

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
    std::vector<vec> points {};

    for (int i = 0; i < edges.size(); i++) {
        lineseg seg = edges.at(i);
        points.emplace_back(*seg.a);
        points.emplace_back(*seg.b);
    }

    this->solution = polygon();
    this->solution.setPoints(points);
}

/*
void solutionMaker::createSolution() {
    // set of all points that are already in the solution
    std::set<vec> available;
    for (int i = 0 ; i < this->points.size(); i++) {
        available.insert(points[i]);
    }

    vec start = *available.begin();
    available.erase(start);0xe,

    llPoint solution = llPoint(start);
    llPoint* cur = &solution;
    llPoint* first = cur;

    // start with shortest edge from starting point
    double minDist = std::numeric_limits<int>::max();
    vec second;
    for (std::set<vec>::iterator i = available.begin(); i != available.end(); i++) {
        double dist = (cur->point - *i).norm();
        if (dist < minDist) {
            minDist = dist;
            second = *i;
        }
    }
    llPoint second_ll(second);
    cur->next = &second_ll;
    second_ll.prev = cur;

//    // randomly get the initial two vertices for our solution
//    vertex start;
//    start.setX(points[0].getX());
//    start.setY(points[0].getY());
//    vertex second;
//    second.setX((&points[0].getEdges()[0].target).getY();
//    second.setY((&points[0].getEdges()[0].target).getX();
//
//    solutionDcel.initialVertices(start, second);
//    used.insert(vec(start.getX(), start.getY()));
//    used.insert(vec(second.getX(), second.getY()));

    // keep adding vertices until polygon contains all points
    while (available.size() > 0) {
        // loop over all potential points to add
        for (std::set<vec>::iterator i = available.begin(); i != available.end(); i++) {
            vec p = *i;

            // create triangle with cur.target, cur.twin.target, p
            // check if there is a point in this triangle, if there is we cannot use this point
            // check if the line segments (cur.target, p) or (cur.twin.target, p) intersect with the current polygon

            // if no problem
            //     add p between cur.twin.target and cur.target and go next
            // else continue
        }
        // being here means we cannot add a point to this edge
        // move to the next edge
    }

}
*/

polygon solutionMaker::getSolution() {
    // we do not have a solution yet
    if (this->solution.getPoints().size() == 0) {
        this->createSolution();
    }
    return this->solution;
}
