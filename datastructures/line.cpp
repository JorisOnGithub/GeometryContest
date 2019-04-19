//
// Created by 20173595 on 02/04/2019.
//

#include "line.h"

bool line::isParallel(const line &l) const {
    return (fabs(this->a - l.a) < EPS && fabs(this->b - l.b) < EPS);
}

bool line::isEqual(const line &l) const {
    return this->isParallel(l) && fabs(this->c - l.c) < EPS;
}

vec line::intersect(const line &l) const {
    if (this->isParallel(l)) throw "lines are parallel, no intersection point";

    // solve 2x2 matrix
    double x = (this->c * l.b - l.c * this->b) / (l.a * this->b - this->a * l.b);
    double y;

    if (fabs(this->b) < EPS) { // this line is vertical
        y = (-l.c - l.a * x) / l.b;
    } else {
        y = (-this->c - this->a * x) / this->b;
    }

    return vec(x, y);
}

// LINE UTILITY

line pointsToLine(const vec &p1, const vec &p2) {
    return line(p1, p2);
}

bool areParallel(const line &l1, const line &l2) {
    return l1.isParallel(l2);
}

bool areEqual(const line &l1, const line &l2) {
    return l1.isEqual(l2);
}

vec intersect(const line &l1, const line &l2) {
    return l1.intersect(l2);
}