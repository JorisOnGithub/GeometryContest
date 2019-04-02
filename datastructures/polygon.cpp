//
// Created by 20173595 on 02/04/2019.
//

#include "polygon.h"
#include "vec.h"

// returns true if c is not to the right of vector ab
bool ccw(const point &a, const point &b, const point &c) {
    return vec(a, b).cross(vec(b, c)) >= 0;
}

void polygon::setPoints(std::vector<point> &points)  {
    this->points = points;
}

std::vector<point> polygon::getPoints() const {
    return this->points;
}

// calculates the area of this polygon
// note that for this contest all areas will be integer, so you can round the returned 'double'
double polygon::area() const {
    double area = 0;

    for (int i = 0; i < this->points.size() - 1; i++) {
        area += this->points[i].x * this->points[i + 1].y;
        area -= this->points[i].y * this->points[i + 1].x;
    }

    return fabs(area) / 2.0;
}

bool polygon::isConvex() const {
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
