//
// Created by joris on 4/25/19.
//

#ifndef GEOMETRY_CONTEST_SOLUTIONMAKER_H
#define GEOMETRY_CONTEST_SOLUTIONMAKER_H

#include "datastructures/polygon.h"
#include "datastructures/dcel/dcel.h"

class solutionMaker {
private:
    polygon solution;
    std::vector<vec> points;
//    dcel* triangulation;

    void createSolution();

public:
    // input t is a triangulation of the input points
    solutionMaker(const &std::vector<vec> pts) {
        this.points = pts;
    }

    polygon getSolution() const;

};


#endif //GEOMETRY_CONTEST_SOLUTIONMAKER_H
