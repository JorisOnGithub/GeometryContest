//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_POLYGON_H
#define GEOMETRY_CONTEST_POLYGON_H

#include "vec.h"
#include "lineseg.h"
#include <vector>

// polygon in 2D space
class polygon {
private:
    // p0, p1, ..., pn, p0. Note that p0 must be at the start and end of this list!
    std::vector<vec> points;

    bool intersects(vec &a, vec &b, vec &p);
public:
    // constructors
    polygon() {}

    polygon(std::vector<vec> &_points) : points(_points) {}

    void setPoints(std::vector<vec> &points);

    std::vector<vec> getPoints() const;

    int getSize() const;

    void removePoint(int index);

    void addPoint(vec &point, int index);

    vec getPoint(int index) const;

    lineseg* getEdge(int index) const;

    double area() const;

    bool isConvex() const;

    bool contains(vec &point);
};


#endif //GEOMETRY_CONTEST_POLYGON_H
