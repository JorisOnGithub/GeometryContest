/* NWERC 2009 solution by Jaap Eldering
 * Problem: Simple Polygon
 */

#include "NWERC09Argafal.h"

using namespace std;

NWERC09Argafal::NWERC09Argafal(const std::vector<vec> &points) {
    int num = points.size();
    Point center;
    center.x = 0;
    center.y = 0;
    for(int i = 0; i< num; i++){
        pts[i].x = points[i].x;
        pts[i].y = points[i].y;
        pts[i].i = i;

        center.x += pts[i].x / (double)num;
        center.y += pts[i].y / (double)num;
    }
    /*
    cout << center.x << endl;
    cout << center.y << endl;
    */
    for(int i = 0; i< num; i++){
        pts[i].angle = atan2(pts[i].y - center.y, pts[i].x - center.x);
        //cout << "angle pts " << pts[i].i << " is " << pts[i].angle << endl;
    }
    qsort(pts, num, sizeof(Point), cmp);
    for(int i = 0; i< num; i++){
        //cout << "angle pts " << pts[i].i << " is " << pts[i].angle << endl;
    }
    vector<vec> resPoints;
    for(int i = 0; i < num; i++) {
        resPoints.push_back(vec(pts[i].x, pts[i].y));
    }
    resPoints.push_back(vec(pts[0].x, pts[0].y));

    resPoly = polygon(resPoints);
}

