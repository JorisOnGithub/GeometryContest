#include "vec.h"
#include "line.h"
#ifndef GEOMETRY_CONTEST_LINESEGMENT_H
#define GEOMETRY_CONTEST_LINESEGMENT_H

class lineseg {
    public:
        vec * a, * b;
    public:
        lineseg(vec *a, vec *b) {
            a = a;
            b = b;
        }

        void setA(vec *newA) {
            a = newA; 
        }

        void setB(vec *newB) {
            b = newB; 
        }

        bool intersects(lineseg other);

        bool intersects(line other);
};
#endif
