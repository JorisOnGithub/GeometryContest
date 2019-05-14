//
// Created by 20173586 on 30/04/2019.
//

#ifndef GEOMETRY_CONTEST_SOLVER_H
#define GEOMETRY_CONTEST_SOLVER_H

#include <iostream>
#include <vector>
#include "../datastructures/vec.h"
#include "../datastructures/polygon.h"

class solver {
private:
    std::string inFile;
    std::string outFile;
    //polygon solution;
    //std::vector<vec> points;


public:
    //solver(const std::vector<vec> &pts) { this->points = pts; }
    //solver(const std::vector<triangle> &triangles_) { this->triangles = triangles_; }
    virtual polygon getSolution();
};


#endif //GEOMETRY_CONTEST_SOLVER_H
