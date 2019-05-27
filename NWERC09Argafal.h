#ifndef GEOMETRY_CONTEST_NWERC09ARGAFAL_H
#define GEOMETRY_CONTEST_NWERC09ARGAFAL_H

#include "datastructures/polygon.h"
#include "io/visualiser.h"
#include <set>
#include "datastructures/lineseg.h"
#include "datastructures/quadtree.h"
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

class NWERC09Argafal {
private:

    struct Point { double x, y; int i; double angle;};

    Point pts[20000];    //gegebene Punkte

    static int cmp(const void *a, const void *b) {
        Point p1 = *((Point *) a);
        Point p2 = *((Point *) b);
        //cout << " compare " << p1.i << " " << p2.i << ": ";
        if(p1.angle - p2.angle > EPS){
            //   cout << "1" << endl;
            return 1;
        }
        if(p1.angle - p2.angle < -EPS) {
            //  cout << "-1" << endl;
            return -1;
        }
        //cout << "0" << endl;
        return 0;
    }

    polygon resPoly;

public:
    // input t is a triangulation of the input points
    NWERC09Argafal(const std::vector<vec> &pts);

    /*
    solutionMaker(const std::vector<triangle> &triangles_) {
        this->triangles = triangles_;
    }
    */

    polygon getSolution() {
        return resPoly;
    }

};

#endif //GEOMETRY_CONTEST_NWERC09ARGAFAL_H
