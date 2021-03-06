//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_VEC_H
#define GEOMETRY_CONTEST_VEC_H

#include <cmath>
#include <string>
const long double EPS = 1e-9;

// vector in 2D space
class vec {
public:
    double x, y;

public:
    // constructors
    vec() {}
    vec(long double _x, long double _y) : x(_x), y(_y) {}

    vec(const vec &a, const vec &b) : vec(b.x - a.x, b.y - a.y) {}

    // operations
    // L2 norm of this vector squared
    long double norm_sq() const;

    // L2 norm of this vector
    long double norm() const;

    // dot product
    long double dot(const vec &v) const;

    // cross product
    long double cross(const vec &v) const;

    // to string
    std::string toString() const;

    // arithmetic
    vec operator+(const vec &p) const {
        return vec(x + p.x, y + p.y);
    }

    vec operator-(const vec &p) const {
        return vec(x - p.x, y - p.y);
    }

    bool operator==(const vec &p) const {
        return fabs(x -p.x) < EPS && fabs(y-p.y) < EPS;
    }

    // default sorting order: y increasing then x increasing
    bool operator<(const vec &p) const {
        if (fabs(y - p.y) < EPS) {
            return x < p.x;
        }
        return y < p.y;
    }
};

// VECTOR
vec toVec(vec a, vec b);

long double norm_sq(vec v);

long double norm(const vec &v);

long double dot(vec a, vec b);

long double cross(vec a, vec b);

#endif //GEOMETRY_CONTEST_VEC_H
