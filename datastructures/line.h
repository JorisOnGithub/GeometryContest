//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_LINE_H
#define GEOMETRY_CONTEST_LINE_H

#include "vec.h"
#include <cmath>

// infinite line in 2D space
class line {
public:
    // ax + by + c = 0
    double a, b, c;

public:
    // constructors
    line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    line(const vec &p1, const vec &p2) {
        if (fabs(p1.x - p2.x) < EPS) { // vertical line
            line(1.0, 0.0, -p1.x);
        } else {
            double dx = p2.x - p1.x;
            double dy = p2.y - p1.y;

            double a = -dy / dx;
            double b = 1.0; // fix at 1.0
            double c = -a * p1.x - p1.y;

            line(a, b, c);
        }
    }

    bool isParallel(const line &l) const;

    bool isEqual(const line &l) const;

    vec intersect(const line &l) const;
};


line pointsToLine(const vec &p1, const vec &p2);

bool areParallel(const line &l1, const line &l2);

bool areEqual(const line &l, const line &l2);

// returns intersection point of line l1 and line l2
vec intersect(const line &l1, const line &l2);


#endif //GEOMETRY_CONTEST_LINE_H
