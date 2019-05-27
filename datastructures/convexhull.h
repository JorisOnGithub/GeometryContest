/**
 * Based on https://www.geeksforgeeks.org/dynamic-convex-hull-adding-points-existing-convex-hull/
 */

#ifndef GEOMETRY_CONTEST_CONVEXHULL_H
#define GEOMETRY_CONTEST_CONVEXHULL_H

#include "polygon.h"
#include <vector>
#include "vec.h"

class convexhull{
private:
    polygon convex;

    int sqDist(const vec &p1, const vec &p2);
    int orientation(const vec &a, const vec &b, const vec &c);
public:
    convexhull(const polygon &poly) {
        this->convex = poly;
    }

    convexhull(std::vector<vec> &points) {
        this->convex = polygon();
        this->convex.setPoints(points);
    }

    void add(vec &p);
    polygon getPoly();
};

#endif // GEOMETRY_CONTEST_CONVEXHULL_H
