//
// Created by Joris on 31/03/2019.
//

#include <algorithm>
#include <set>
#include "simpleChecker.h"

// checks if p is to the left of, on, or to the right of line segment ab
// return < 0 if left, 0 if on, > 0 if right
double isLeft(const point &a, const point &b, const point &p) {
    // (l.rP - l.lP) and (p - l.lP)
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

bool intersect(const SLseg &a, const SLseg &b) {
    // intersection at vertex that is in both segments does not count
    if (a.edge == b.edge + 1 || b.edge == a.edge + 1) return false;

    double l_sign, r_sign;
    l_sign = isLeft(a.lP, a.rP, b.lP);
    r_sign = isLeft(a.lP, a.rP, b.rP);
    if (l_sign * r_sign > 0) return false; // both endpoints on the same side of line
    l_sign = isLeft(b.lP, b.rP, a.lP);
    r_sign = isLeft(b.lP, b.rP, a.rP);
    if (l_sign * r_sign > 0) return false;
    return true;
}

bool isSimple(const polygon &P) {
    std::vector<point> pts = P.getPoints();
    int n = (int) pts.size() - 1;
    std::vector<event> EQ; // event queue

    // create events
    for (int i = 0; i < n; i++) {
        SLseg seg = SLseg(pts[i], pts[i + 1], i);
        bool isOrder = pts[i].x <= pts[i + 1].x;
        SEG_SIDE type = isOrder ? LEFT : RIGHT;
        EQ.emplace_back(event(type, pts[i], seg));
        EQ.emplace_back(event(isOrder ? RIGHT : LEFT, pts[i + 1], seg));
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

bool simpleChecker::isSimple() const {
    return ::isSimple(this->P);
}
