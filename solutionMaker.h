//
// Created by joris on 4/25/19.
//

#ifndef GEOMETRY_CONTEST_SOLUTIONMAKER_H
#define GEOMETRY_CONTEST_SOLUTIONMAKER_H

#include "datastructures/polygon.h"
#include "datastructures/triangle.h"

class solutionMaker {
private:
    polygon solution;
    std::vector<vec> points;
    std::vector<triangle> triangles;
//    dcel* triangulation;

    void createSolution();

public:
    // input t is a triangulation of the input points
    solutionMaker(const std::vector<vec> &pts) {
        this->points = pts;
    }

    solutionMaker(const std::vector<triangle> &triangles_) {
        this->triangles = triangles_;
    }

    polygon getSolution();

};


#endif //GEOMETRY_CONTEST_SOLUTIONMAKER_H
