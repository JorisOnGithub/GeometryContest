//
// Created by Joris on 27/03/2019.
//

#include "datastructures.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <set>

// POINT UTILITY

// euclidean distance
double dist(const point &p1, const point &p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

bool equal(const point &a, const point &b) {
    return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS;
}

// LINE UTILITY

line pointsToLine(const point &p1, const point &p2) {
    if (fabs(p1.x - p2.x) < EPS) { // vertical line
        return line(1.0, 0.0, -p1.x);
    }

    double dx = (double) p2.x - p1.x;
    double dy = (double) p2.y - p1.y;
    double a = -dy / dx;
    double b = 1.0;
    double c = -a * p1.x - p1.y;

    return line(a, b, c);
}

bool areParallel(const line &l1, const line &l2) {
    return (fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS);
}

bool areEqual(const line &l1, const line &l2) {
    return areParallel(l2, l2) && fabs(l1.c - l2.c) < EPS;
}

point intersect(const line &l1, const line &l2) {
    if (areParallel(l1, l2)) throw "lines are parallel, no intersection point";

    double x = (l1.c * l2.b - l2.c * l1.b) / (l2.a * l1.b - l1.a * l2.b);
    double y;
    if (fabs(l1.b) < EPS) { // line 1 is vertical
        y = -l2.c - l2.a * x / l2.b;
    } else {
        y = -l1.c - l1.a * x / l1.b;
    }

    return point(x, y);
}

// VECTOR UTILITY

vec toVec(point a, point b) {
    return vec(b.x - a.x, b.y - a.y);
}

double dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

double norm_sq(vec v) {
    return v.x * v.y + v.y * v.y;
}

double cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

// returns true if c is not to the right of line ab
bool ccw(point a, point b, point c) {
    return cross(toVec(a, b), toVec(b, c)) >= 0;
}

// POLYGON UTILITY

// calculates the area of this polygon
// note that for this contest all areas will be integer, so you can round this double
double polygon::area() {
    double area = 0;

    for (int i = 0; i < this->points.size() - 1; i++) {
        area += this->points[i].x * this->points[i + 1].y;
        area -= this->points[i].y * this->points[i + 1].x;
    }

    return fabs(area) / 2.0;
}

bool polygon::isConvex() {
    int size = (int) points.size();

    // polygon is point or line segment
    if (size <= 3) return false;

    bool sign = ccw(points[0], points[1], points[2]);

    for (int i = 1; i < points.size() - 2; i++) {
        if (ccw(points[i], points[i + 1], points[i + 2]) != sign) {
            return false; // polygon is concave
        }
    }

    return true;
}
