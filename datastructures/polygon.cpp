//
// Created by 20173595 on 02/04/2019.
//

#include "polygon.h"
#include <iostream>
#include <limits>
#include <algorithm>

// returns true if c is not to the right of vector ab
bool ccw(const vec &a, const vec &b, const vec &c) {
    return vec(a, b).cross(vec(b, c)) >= 0;
}

void polygon::setPoints(std::vector<vec> &points)  {
    this->points = points;
}

std::vector<vec> polygon::getPoints() const {
    return this->points;
}

// calculates the area of this polygon
// note that for this contest all areas will be integer, so you can round the returned 'double'
double polygon::area() const {
    double area = 0;
//    std::cout << "get area" << std::endl;
    for (int i = 0; i < this->points.size() - 1; i++) {
//        std::cout << points[i].x << " " << points[i].y << " " << area << std::endl;
        area += this->points[i].x * this->points[i + 1].y;
        area -= this->points[i].y * this->points[i + 1].x;
    }

//    std::cout << "done: "<< fabs(area) / 2.0 <<  std::endl;

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
/* check if point p intersects an edge(a,b) */
bool polygon::intersects(vec &a, vec &b, vec &p) {
    if (a.y > b.y) {
        return this->intersects(b, a, p);
    }

    if (p.y == a.y || p.y == b.y) {
        double eps = std::numeric_limits<float>().epsilon();
        vec np(p.x, p.y + eps);

        return intersects(a, b, np);
    }

    if (p.y > b.y || p.y < a.y || p.x >= std::max(a.x, b.x))
        return false;

    if (p.x < std::min(a.x, b.x))
        return true;

    double red = (p.y - a.y) / (p.x - a.x);
    double blue = (b.y - a.y) / (b.x - a.x);

    return red >= blue;
}

/* check if a point is contained in this polygon */
bool polygon::contains(vec &point) {
    int len = this->points.size();
    bool inside = false;

    // can be split into multiple threads if end results are combined
    for (int i = 0; i < len; i++) {
        if (this->intersects(this->points[i], this->points[(i+1) % len], point)) {
            inside = !inside;
        }
    }
//    std::cout << "does it contain the point: " << inside << std::endl;
    return inside;
}


int polygon::getSize() const {
    return this->points.size() - 1;
}

vec polygon::getPoint(int index) const {
    index %= this->getSize();
    return this->points[index];
}

void polygon::removePoint(int index) {
//    std::cout << " ----------- remove point: " << index << std::endl;
//    std::cout << "before removing: " << std::endl;
//    for (vec point : this-> points) {
//        std::cout << point.x << " " << point.y << std::endl;
//    }
    this->points.erase(this->points.begin() + index);

//    std::cout << "after first removal: " << std::endl;
//    for (vec point : this-> points) {
//        std::cout << point.x << " " << point.y << std::endl;
//    }
    if (index == 0) {
        this->points.erase(this->points.end() - 1);
        this->points.push_back(this->points[0]);
    } else if (index == this->getSize() + 1) {
        this->points.erase(this->points.begin());
//        std::cout << "after second removal: " << std::endl;
//        for (vec point : this-> points) {
//            std::cout << point.x << " " << point.y << std::endl;
//        }
        this->points.push_back(this->points[0]);
    }

//    std::cout << "final list " << std::endl;
//    for (vec point : this-> points) {
//        std::cout << point.x << " " << point.y << std::endl;
//    }
//    std::cout << "-----------remove point done" << std::endl;
}
//TODO: should be added at index i or after index i
void polygon::addPoint(vec &point, int index) {
    index %= (this->getSize());
//    std::cout << "addPoint " << index << " " << point.x << " " << point.y << std::endl;
//    for (vec point : this->points) {
//        std::cout << point.x << " " << point.y << std::endl;
//    }
//    std::cout << "and then "<< std::endl;
    this->points.insert(this->points.begin() + index, point);
    if (index == 0) {
        this->points.erase(this->points.end() - 1);
        this->points.push_back(point);
    }
//    for (vec point : this->points) {
//        std::cout << point.x << " " << point.y << std::endl;
//    }
}

lineseg polygon::getEdge(int index) const {
    vec p1 = this->points[index];
    vec p2 = this->points[(index + 1) % (this->getSize())];
    return lineseg(&p1, &p2);
}