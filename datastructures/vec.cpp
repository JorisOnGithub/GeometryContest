//
// Created by 20173595 on 02/04/2019.
//

#include "vec.h"

// L2 norm of this vector squared
long double vec::norm_sq() const {
    return this->x * this->x + this->y * this->y;
}

// L2 norm of this vector
long double vec::norm() const {
    return sqrt(this->norm_sq());
}

// dot product
long double vec::dot(const vec &v) const {
    return this->x * v.x + this->y * v.y;
}

// size of the cross product, < 0 if right product, > 0 if left product
long double vec::cross(const vec &v) const {
    return this->x * v.y - this->y * v.x;
}

std::string vec::toString() const {
    std::string res = "(";
    res += std::to_string(this->x);
    res += ",";
    res += std::to_string(this->y);
    res += ")";
    return res;
}

// VECTOR UTILITY

vec toVec(const vec &a, const vec &b) {
    return vec(a, b);
}

long double norm_sq(const vec &v) {
    return v.norm_sq();
}

long double norm(const vec &v) {
    return v.norm();
}

long double cross(const vec &a, const vec &b) {
    return a.cross(b);
}

long double dot(const vec &a, const vec &b) {
    return a.dot(b);
}