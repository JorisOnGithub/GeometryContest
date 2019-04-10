//
// Created by Joris on 31/03/2019.
//

#ifndef GEOMETRY_CONTEST_SIMPLECHECKER_H
#define GEOMETRY_CONTEST_SIMPLECHECKER_H

//
// Created by Joris on 31/03/2019.
//

#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include "datastructures/polygon.h"

enum SEG_SIDE {
    LEFT, RIGHT
};

class simpleChecker {
private:
    polygon P;

public:
    simpleChecker(const polygon &_P) : P(_P) {}

    // n^2 simple check
    bool isSimpleSlow() const;

    // n log n simple check
    bool isSimple() const;
};

double isLeft(const vec &a, const vec &b, const vec &p);

// sweeping line segment
class SLseg {
public:
    int edge;
    vec lP, rP; // lP.x < rP.x, if lP.x == rP.x then lP.y <= rP.y

    SLseg(vec _a, vec _b, int _edge) {
        this->edge = _edge;
        if (fabs(_a.x - _b.x) < EPS) { // same x
            if (_b.y < _a.y) {
                lP = _b;
                rP = _a;
            } else {
                lP = _a;
                rP = _b;
            }
        } else {
            if (_a.x < _b.x) {
                lP = _a;
                rP = _b;
            } else {
                lP = _b;
                rP = _a;
            }
        }
    }

    bool intersect(const SLseg &o) const;

    // sort segments on increasing y on sweeping line
    bool operator<(const SLseg &o) const {
        if (lP.x <= o.lP.x) {
            double s = isLeft(lP, rP, o.lP);
            if (s != 0) return s > 0;
            else { // o.lP is on this segment
                if (lP.x == rP.x) { // this segment is vertical
                    return lP.y < o.lP.y; // increasing y
                } else return isLeft(lP, rP, o.rP) > 0;
            }
        } else {
            double s = isLeft(o.lP, o.rP, lP);
            if (s != 0) return s < 0;
            else return isLeft(o.lP, o.rP, rP) < 0;
        }
    }

};

bool intersect(const SLseg &a, const SLseg &b);

// event for in the event queue
class event {
public:
    SEG_SIDE type; // type of event
    vec *eP; // event point
    SLseg *seg; // segment related to this event

    event(SEG_SIDE type, vec &p, SLseg &_seg) {
        this->type = type;
        this->eP = &p;
        this->seg = &_seg;
    }

    // sort events on increasing x coordinate and else increasing y coordinate
    bool operator<(const event &e) const {
        if (fabs(eP->x - e.eP->x) < EPS) {
            return eP->y > e.eP->y;
        }
        return eP->x < e.eP->x;
    }
};


bool isSimple(const polygon &P);


#endif //GEOMETRY_CONTEST_SIMPLECHECKER_H
