//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_VEC_H
#define GEOMETRY_CONTEST_VEC_H

#include "point.h"

// vector in 2D space
class vec {
public:
    double x, y;

public:
    // constructors
    vec(double _x, double _y) : x(_x), y(_y) {}

    vec(const point &a, const point &b) : vec(b.x - a.x, b.y - a.y) {}

    // operations

    // L2 norm of this vector squared
    double norm_sq() const;

    // L2 norm of this vector
    double norm() const;

    // dot product
    double dot(const vec &v) const;

    // cross product
    double cross(const vec &v) const;
};

// VECTOR
vec toVec(point a, point b);

double norm_sq(vec v);

double norm(const vec &v);

double dot(vec a, vec b);

double cross(vec a, vec b);

#endif //GEOMETRY_CONTEST_VEC_H
