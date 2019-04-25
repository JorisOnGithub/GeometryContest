//
// Created by joris on 4/25/19.
//

#ifndef GEOMETRY_CONTEST_TRIANGLE_H
#define GEOMETRY_CONTEST_TRIANGLE_H

#include "vec.h"

class triangle {
private:
    vec p1, p2, p3;

public:
    triangle(const vec &v1, const vec &v2, const vec &v3) {
        p1 = v1;
        p2 = v2;
        p3 = v3;
    }

    bool containsPoint(const vec &v) const;

};


#endif //GEOMETRY_CONTEST_TRIANGLE_H
