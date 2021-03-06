/* NWERC 2009 solution by Jaap Eldering
 * Problem: Simple Polygon
 */

#include "NWERC09Jaap.h"

using namespace std;

NWERC09Jaap::NWERC09Jaap(const std::vector<vec> &pts) {
    int N = pts.size()-1;
    points = vector<point>(N);

    for(int i=0; i<N; i++) {
        points[i].x = pts[i].x;
        points[i].y = pts[i].y;
        points[i].index = i;
    }

    VI res, used(N,0);

    res = convexhalfhull();
    vector<vec> resPoints;

    for(size_t i=0; i<res.size(); i++) used[res[i]] = 1;

    for(int i=N-1; i>=0; i--) {
        if ( !used[i] ) {
            res.push_back(i);
        }
    }

    for (int i = 0; i < res.size(); i++) {
        resPoints.push_back(vec(pts[res[i]].x, pts[res[i]].y));
    }
    resPoints.push_back(vec(pts[res[0]].x, pts[res[0]].y));

    resPoly = polygon(resPoints);
}

