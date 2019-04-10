//
// Created by 20173595 on 02/04/2019.
//

#include "vec.h"
#include <cmath>

// L2 norm of this vector squared
double vec::norm_sq() const {
    return this->x * this->x + this->y * this->y;
}

// L2 norm of this vector
double vec::norm() const {
    return sqrt(this->norm_sq());
}

// dot product
double vec::dot(const vec &v) const {
    return this->x * v.x + this->y * v.y;
}

// size of the cross product, < 0 if right product, > 0 if left product
double vec::cross(const vec &v) const {
    return this->x * v.y - this->y * v.x;
}

// VECTOR UTILITY

vec toVec(const vec &a, const vec &b) {
    return vec(a, b);
}

double norm_sq(const vec &v) {
    return v.norm_sq();
}

double norm(const vec &v) {
    return v.norm();
}

double cross(const vec &a, const vec &b) {
    return a.cross(b);
}

double dot(const vec &a, const vec &b) {
    return a.dot(b);
}