//
// Created by Joris on 31/03/2019.
//

#include <algorithm>
#include <set>
#include "simpleChecker.h"

// checks if p is to the left of, on, or to the right of line segment ab
// return < 0 if left, 0 if on, > 0 if right
double isLeft(const vec &a, const vec &b, const vec &p) {
    // (l.rP - l.lP) and (p - l.lP)
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

bool SLseg::intersect(const SLseg &o) const {
    // intersection at vertex that is in both segments does not count
    if (this->edge == o.edge + 1 || this->edge + 1 == o.edge) return false;
    if (this->lP == o.lP || this->lP == o.rP || this->rP == o.lP || this->rP == o.rP) {
        return false;
    }

    double l_sign, r_sign;
    l_sign = isLeft(this->lP, this->rP, o.lP);
    r_sign = isLeft(this->lP, this->rP, o.rP);
    if (l_sign * r_sign > 0) return false; // both endpoints on the same side of line

    l_sign = isLeft(o.lP, o.rP, this->lP);
    r_sign = isLeft(o.lP, o.rP, this->rP);
    if (l_sign * r_sign > 0) return false;
    return true;
}

bool intersect(const SLseg &a, const SLseg &b) {
    return a.intersect(b);
}

bool isSimple(const polygon &P) {
    simpleChecker sC(P);
    return sC.isSimpleSlow();
}

bool simpleChecker::isSimpleSlow() const {
    std::vector<vec> pts = this->P.getPoints();
    int n = (int) pts.size() - 1;

    std::vector<SLseg> segments;
    for (int i = 0; i < n; i++) {
        SLseg seg = SLseg(pts[i], pts[i + 1], i);
        segments.push_back(seg);
    }

    // check quadratic intersections between n sections
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (segments[i].intersect(segments[j])) return false;
        }
    }

    return true;
}

bool simpleChecker::isSimple() const {
    std::vector<vec> pts = this->P.getPoints();
    int n = (int) pts.size() - 1;
    std::vector<event> EQ; // event queue

    // create events
    for (int i = 0; i < n; i++) {
        SLseg seg = SLseg(pts[i], pts[i + 1], i);
        bool isOrder = pts[i].x <= pts[i + 1].x;
        SEG_SIDE type = isOrder ? LEFT : RIGHT;
        EQ.emplace_back(event(type, pts[i], seg)); // first point
        EQ.emplace_back(event(isOrder ? RIGHT : LEFT, pts[i + 1], seg)); // second point
    }
    std::sort(EQ.begin(), EQ.end());

    std::set<SLseg> line; // current sweeping line

    for (int i = 0; i < 2 * n; i++) {
        event e = EQ[i];

        if (e.type == LEFT) {
            std::set<SLseg>::iterator it;

            // check if current segment intersects with line below
            it = line.upper_bound(*e.seg);
            if (it != line.end()) {
                if (intersect(*it, *e.seg)) return false;
            }
            // check if current segment intersects with line above
            it = line.lower_bound(*e.seg);
            if (it != line.end()) {
                if (intersect(*it, *e.seg)) return false;
            }
            // insert this segment
            line.insert(*e.seg);
        } else {
            line.erase(*e.seg); // remove from sweeping line

            // check if its neighbours intersect
            auto up = line.lower_bound(*e.seg);
            auto down = line.upper_bound(*e.seg);
            if (up != line.end() && down != line.end()) {
                if (intersect(*up, *down)) return false;
            }
        }
    }

    return true;
}
