#include "vec.h"
#include "line.h"
#include <iostream>
#ifndef GEOMETRY_CONTEST_LINESEGMENT_H
#define GEOMETRY_CONTEST_LINESEGMENT_H

class lineseg {
    public:
        vec a, b;
    public:
        lineseg(vec *a, vec *b) {
            this->a = *a;
            this->b = *b;
        }

        void set_a(vec *new_a) {
            this->a = *new_a; 
        }

        void set_b(vec *new_b) {
            this->b = *new_b; 
        }

        bool intersects(lineseg &other);

        std::string toString() const;


        bool operator <(const lineseg &other) const {
            return this->a < other.a;
        }

        bool operator ==(const lineseg &other) const {
            return (this->a == other.a && this->b == other.b) ||
                    (this->b == other.a && this->a == other.b);
        }
        bool operator !=(const lineseg &other) const {
            return !(*this == other);
        }
};
#endif
