//
// Created by Joris on 31/03/2019.
//

#ifndef GEOMETRY_CONTEST_SIMPLECHECKER_H
#define GEOMETRY_CONTEST_SIMPLECHECKER_H

//
// Created by Joris on 31/03/2019.
//

#include "datastructures.h"
#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

enum SEG_SIDE {
    LEFT, RIGHT
};

double isLeft(const point &a, const point &b, const point &p);

// sweeping line segment
class SLseg {
public:
    int edge;
    point lP, rP; // lP.x < rP.x, if lP.x == rP.x then lP.y <= rP.y

    SLseg(point _a, point _b, int _edge) {
        this->edge = edge;
        if (_a.y >= _b.y) {
            lP = _a;
            rP = _b;
        } else {
            lP = _b;
            rP = _a;
        }
    }

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
    point *eP; // event point
    SLseg *seg; // segment related to this event

    event(SEG_SIDE type, point &p, SLseg &_seg) {
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


bool isSimple(polygon &P);


#endif //GEOMETRY_CONTEST_SIMPLECHECKER_H
