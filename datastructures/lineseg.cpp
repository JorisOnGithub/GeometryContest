#include "lineseg.h"
#include "vec.h"
#include<iostream>

#define colinear 0
#define ccw 1
#define anticcw 2

bool onLine(vec &p, vec &q, vec &r) {   //check whether p is on the line or not
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
           q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
}

int direction(vec &a, vec &b, vec &c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) {
        return colinear;     //colinear
    }
    return (val > 0) ? ccw : anticcw;
}

std::string lineseg::toString() const {
    std::string res = this->a.toString();
    res += " -> ";
    res += this->b.toString();
    return res;
}

// checks if p is to the left of, on, or to the right of line segment ab
// return < 0 if left, 0 if on, > 0 if right
double lineseg::isLeft(const vec &a, const vec &b, const vec &p) {
    // (l.rP - l.lP) and (p - l.lP)
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}


bool lineseg::intersects(lineseg &other) {
    if (this->a == other.a || this->a == other.b || this->b == other.a || this->b == other.b) {
        // they share a point, do not count this as intersection, only useful for greedy algo
        return false;
    }

    double l_sign, r_sign;
    l_sign = isLeft(a, b, other.a);
    r_sign = isLeft(a, b, other.b);
    if (l_sign * r_sign > 0) return false; // both endpoints on the same side of line

    l_sign = isLeft(other.a, other.b, a);
    r_sign = isLeft(other.a, other.b, b);
    if (l_sign * r_sign > 0) return false;
    return true;
    /*

    //four direction for two lines and points of other line
    int dir1 = direction(this->a, this->b, other.a);
    int dir2 = direction(this->a, this->b, other.b);
    int dir3 = direction(other.a, other.b, this->a);
    int dir4 = direction(other.a, other.b, this->b);

    if (dir1 != dir2 && dir3 != dir4) {
        return true; //they are intersecting
    }

    if (dir1 == 0 && onLine(this->a, other.a, this->b)) {//when p2 of line2 are on the line1
        return true;
    }

    if (dir2 == 0 && onLine(this->a, other.b, this->b)) {//when p1 of line2 are on the line1
        return true;
    }

    if (dir3 == 0 && onLine(other.a, this->a, other.b)) {//when p2 of line1 are on the line2
        return true;
    }

    if (dir4 == 0 && onLine(other.a, this->b, other.b)) {//when p1 of line1 are on the line2
        return true;
    }
    return false;
     */
}

bool lineseg::ray_intersects(lineseg &other) {
    if (this->a == other.a || this->a == other.b) {
        // they share a point, do not count this as intersection
        return false;
    }

    double l_sign, r_sign;
    l_sign = isLeft(a, b, other.a);
    r_sign = isLeft(a, b, other.b);
    if (l_sign * r_sign > 0) return false; // both endpoints on the same side of ray

    double x1 = this->a.x;
    double y1 = this->a.y;
    double x2 = this->b.x;
    double y2 = this->b.y;

    double x3 = other.a.x;
    double y3 = other.a.y;
    double x4 = other.b.x;
    double y4 = other.b.y;

    double t = (y3-y4)*(x1-x3) + (x4-x3)*(y1-y3);
    t /= (x4-x3) * (y1-y2) - (x1-x2) * (y4-y3);
    if (t <= 0) return false;

    return true;
}

vec lineseg::pointOfIntersection(lineseg &other) {
    if (!intersects(other)) {
        return vec(-M_PI, -M_PI);
    } else {
        // using http://www.cs.swan.ac.uk/~cssimon/line_intersection.html
        double x1 = this->a.x;
        double y1 = this->a.y;
        double x2 = this->b.x;
        double y2 = this->b.y;

        double x3 = other.a.x;
        double y3 = other.a.y;
        double x4 = other.b.x;
        double y4 = other.b.y;

        double t = (y3-y4)*(x1-x3) + (x4-x3)*(y1-y3);
        t /= (x4-x3) * (y1-y2) - (x1-x2) * (y4-y3);

        // TODO: Someone should check this, but I think that this should be:
        // TODO: return vec(x1 + t * (x2 - x1), y1 + t * (y2 - y1));
        return vec(x1 - t * (x2 - x1), y1 - t * (y2 - y1));
    }
}

double lineseg::ray_dist_to_intersection(lineseg &other) {
    if (!ray_intersects(other)) {
        return -1;
    }
    double x1 = this->a.x;
    double y1 = this->a.y;
    double x2 = this->b.x;
    double y2 = this->b.y;

    double x3 = other.a.x;
    double y3 = other.a.y;
    double x4 = other.b.x;
    double y4 = other.b.y;

    double t = (y3-y4)*(x1-x3) + (x4-x3)*(y1-y3);
    t /= (x4-x3) * (y1-y2) - (x1-x2) * (y4-y3);
    return t;
}
