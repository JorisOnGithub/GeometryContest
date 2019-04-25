//
// Created by joris on 4/25/19.
//

#ifndef GEOMETRY_CONTEST_TRIANGLE_H
#define GEOMETRY_CONTEST_TRIANGLE_H

#include "vec.h"
#include "lineseg.h"
#include <vector>

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

    std::vector<lineseg> getEdges() {
        lineseg e1(&p1, &p2);
        lineseg e2(&p2, &p3);
        lineseg e3(&p3, &p1);

        std::vector<lineseg> linesegs {};
        linesegs.emplace_back(e1);
        linesegs.emplace_back(e2);
        linesegs.emplace_back(e3);

        return linesegs;
    }

};


#endif //GEOMETRY_CONTEST_TRIANGLE_H
