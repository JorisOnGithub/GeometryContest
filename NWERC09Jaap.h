#ifndef GEOMETRY_CONTEST_NWERC09JAAP_H
#define GEOMETRY_CONTEST_NWERC09JAAP_H

#include "datastructures/polygon.h"
#include "io/visualiser.h"
#include <set>
#include "datastructures/lineseg.h"
#include "datastructures/quadtree.h"
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

class NWERC09Jaap {
private:

    typedef vector<int> VI;

    typedef int coord;

    class point {
    public:
        coord x, y;
        int index;

        point() { x = y = 0; }
        point(coord x1, coord y1) { x = x1; y = y1; }

        point operator +=(point a) { x += a.x; y += a.y; return *this; }
        point operator -=(point a) { x -= a.x; y -= a.y; return *this; }

        point operator +(point b) { return *this += b; }
        point operator -(point b) { return *this -= b; }
        coord operator *(point b) { return this->x*b.x + this->y*b.y; }

        int operator <(point b)
        {
            if ( this->x!=b.x ) return this->x < b.x;
            return this->y < b.y;
        }
    };

    coord cross(point a, point b) { return a.x*b.y - a.y*b.x; }

    vector<point> points;

    VI convexhalfhull()
    {
        VI upper;

        // sort points on x-coordinate:
        sort(points.begin(),points.end());

        // build upper part of convex hull (including collinear intermediate points):
        upper.push_back(0);
        for(size_t i=1; i<points.size(); i++) {
            while ( upper.size()>1 &&
                    cross(points[*(upper.end()-1)]-points[*(upper.end()-2)],
                          points[i]               -points[*(upper.end()-2)])>0 ) upper.pop_back();
            upper.push_back(i);
        }

        return upper;
    }

    polygon resPoly;

public:
    // input t is a triangulation of the input points
    NWERC09Jaap(const std::vector<vec> &pts);

    /*
    solutionMaker(const std::vector<triangle> &triangles_) {
        this->triangles = triangles_;
    }
    */

    polygon getSolution() {
        return resPoly;
    }

};

#endif //GEOMETRY_CONTEST_NWERC09JAAP_H
