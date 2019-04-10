//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_POLYGON_H
#define GEOMETRY_CONTEST_POLYGON_H

#include "vec.h"
#include <vector>

// polygon in 2D space
class polygon {
private:
    // p0, p1, ..., pn, p0. Note that p0 must be at the start and end of this list!
    std::vector<vec> points;

public:
    // constructors
    polygon() {}

    polygon(std::vector<vec> &_points) : points(_points) {}

    void setPoints(std::vector<vec> &points);

    std::vector<vec> getPoints() const;

    double area() const;

    bool isConvex() const;
};


#endif //GEOMETRY_CONTEST_POLYGON_H
