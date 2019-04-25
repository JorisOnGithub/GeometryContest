//
// Created by joris on 4/25/19.
//

#include "solutionMaker.h"

struct llPoint {
    vec point;
    llPoint* next;
    llPoint* prev;

    llPoint(vec &p) {
        point = vec;
    }
};



void solutionMaker::createSolution() {
    // set of all points that are already in the solution
    std::set<vec> available;
    for (int i = 0 ; i < this->points.size(); i++) {
        available.insert(points);
    }

    vec start = *available.begin();
    available.erase(start);

    llPoint solution = llPoint(start);
    llPoint* cur = solution;

    // start with shortest edge from starting point
    double minDist = INT_MAX;
    for (std::set<vec>::iterator i = available.begin: i != available.end(); i++) {
        double dist = dist(start)

    }

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
        halfedge cur = start.getEdges()[0];
        // loop over all potential points to add
        for (int i = 0; i < points.size(); i++) {
            vec p = vec(points[i].getX(), points[i].getY());
            // point already in polygon
            if (std::find(used.start(), used.end(), p) != used.end()) continue;

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

polygon solutionMaker::getSolution() const {
    // we do not have a solution yet
    if (this->solution.getPoints().size() == 0) {
        this->createSolution();
    }
    return this->solution;
}
