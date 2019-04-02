//
// Created by 20173595 on 02/04/2019.
//

#ifndef GEOMETRY_CONTEST_POINT_H
#define GEOMETRY_CONTEST_POINT_H

#include <cmath>

const double EPS = 1e-9;

// point in 2D space
class point {
public:
    double x, y; // exact coordinates
    int xi, yi; // integer coordinates
    int index; // optional index in original input

public:
    // constructors
    point() {
        x = y = xi = yi = index = 0;
    }

    point(double _x, double _y, int idx = 0) : x(_x), y(_y), xi((int) _x), yi((int) _y), index(idx) {}

    point(int _x, int _y, int idx = 0) : x((double) _x), y((double) _y), xi(_x), yi(_y), index(idx) {}


    // arithmetic
    point operator+(const point &p) const {
        return point(x + p.x, y + p.y);
    }

    point operator-(const point &p) const {
        return point(x - p.x, y - p.y);
    }

    // default sorting order: y increasing then x increasing
    bool operator<(point p) const {
        if (fabs(y - p.y) < EPS) {
            return x < p.x;
        }
        return y < p.y;
    }

    // euclidean distance to point p
    double dist(const point &p) const;

    // equality of x and y coordinate
    bool equal(const point &p) const;
};


// POINT UTILITY

double dist(const point &p1, const point &p2);

bool equal(const point &a, const point &b);

#endif //GEOMETRY_CONTEST_POINT_H
