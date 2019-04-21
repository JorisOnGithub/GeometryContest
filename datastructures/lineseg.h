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

        void set_a(vec *new_a) {
            a = new_a; 
        }

        void set_b(vec *new_b) {
            b = new_b; 
        }

        bool intersects(lineseg *other);

        bool intersects(line *other);
};
#endif
