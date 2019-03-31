//
// Created by Joris on 27/03/2019.
//

#ifndef GEOMETRY_CONTEST_DATASTRUCTURES_H
#define GEOMETRY_CONTEST_DATASTRUCTURES_H

#include <cmath>
#include <vector>

const double EPS = 1e-9;
const double PI = 3.141592653589793238463;

class point {
public:
    double x, y; // coordinates
    int index; // index in original input

    point() {}

public:
    point(double nx, double ny) : x(nx), y(ny) {
    }

    point(double nx, double ny, int idx) : x(nx), y(ny), index(idx) {
    }

    point operator+(const point &p) const {
        return point(x + p.x, y + p.y);
    }

    point operator-(const point &p) const {
        return point(x - p.x, y - p.y);
    }

    // sort on y increasing, then x increasing
    bool operator<(point p) const {
        if (fabs(y - p.y) < EPS) {
            return x < p.x;
        }
        return y < p.y;
    }
};

class vec {
public:
    double x, y;

    vec(double _x, double _y) : x(_x), y(_y) {
    }

};

class line {
public:
    // ax + by + c = 0
    double a, b, c;

public:
    line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {
    }
};

class polygon {
private:
    // p0, p1, ..., pn, p0
    std::vector<point> points;

public:

    polygon() {}

    polygon(std::vector<point> &_points) : points(_points) {}

    void setPoints(std::vector<point> &points) {
        this->points = points;
    }

    std::vector<point> getPoints() {
        return points;
    }

    double area();

    bool isConvex();
};

// LINE

line pointsToLine(const point &p1, const point &p2);

bool areParallel(const line &l1, const line &l2);

bool areEqual(const line &l, const line &l2);

point intersect(const line &l1, const line &l2);


// VECTOR

vec toVec(point a, point b);

double dot(vec a, vec b);

double norm_sq(vec v);

double cross(vec a, vec b);


#endif //GEOMETRY_CONTEST_DATASTRUCTURES_H
