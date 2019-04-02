//
// Created by 20173595 on 02/04/2019.
//

#include "point.h"

double point::dist(const point &p) const {
    return hypot(this->x - p.x, this->y - p.y);
}

bool point::equal(const point &p) const {
    return (fabs(this->x - p.x) < EPS && fabs(this->y - p.y) < EPS);
}

// separate functions
double dist(const point &p1, const point &p2) {
    return p1.dist(p2);
}

bool equal(const point &a, const point &b) {
    return a.equal(b);
}