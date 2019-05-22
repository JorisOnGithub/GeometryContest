#include "convexhull.h"
#include <iostream>

int convexhull::sqDist(const vec &p1, const vec &p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
        (p1.y - p2.y) * (p1.y - p2.y);
}

/**
 * Check whenether the points crosses the convex hull.
 * TODO: Add enums
 */
int convexhull::orientation(const vec &a, const vec &b, const vec &c) {
    int res = (b.y - a.y) * (c.x - b.x) - (c.y - b.y) * (b.x - a.x);

    if (res == 0) {
        return 0;
    }

    return res > 0 ? 1 : -1;
}

void convexhull::add(vec &p) {
    /*
     * Check if the point is inside the convex hull.
     * This can be faster if needed.
     */
    if (this->convex.contains(p)) {
        return;
    }

    // point having minimum distance from the point p
    int ind = 0;
    std::vector<vec> points = this->convex.getPoints();
    int n = points.size();
    for (int i = 0; i < n; i++) {
        if (this->sqDist(p, points[i]) < sqDist(p, points[ind])) {
            ind = i;
        }
    }

    /* find upper tangent. */
    int up = ind;
    while(orientation(p, points[up], points[(up+1)%n]) >= 0) {
        up = (up+1) %n;
    }

    /* find lowest tangent. */
    int low = ind;
    while (orientation(p, points[low], points[(n+low-1)%n]) <= 0) {
        low = (n+low - 1) % n;
    }

    std::vector<vec> result;
    
    /**
     * Making the final hull by traversing points
     * from up to low given convex hull.
     */
    int cur = up;
    result.push_back(points[cur]);

    while (cur != low) {
        cur = (cur + 1) %n;
        result.push_back(points[cur]);
    }

    result.push_back(p);
    points.clear();

    for (int i = 0; i < result.size(); i++) {
        points.push_back(result[i]);
    }

    this->convex.setPoints(points);
}

polygon convexhull::getPoly() {
    return this->convex;
}
