#include "localOptimizer.h"

void optimizePolygon(polygon &poly, quadtree &qt) {
    optimizePolygonWithPoint(poly, qt, 0);
}

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi) {
    if (!canBeRemoved(poly, qt, pi)) {
        return;
    }
    std::vector<vec> pointList = poly.getPoints();
    pointList.erase(pointList.begin() + pi);
    std::vector<int> si = {};
    for (int i = pi-10; i < 10; i++) {
        i %= poly.getPoints().size()-1;
    }
}

bool canBeRemoved(polygon &poly, quadtree &qt, int pi) {
    std::vector<vec> pointList = poly.getPoints();
    lineseg l = lineseg(&pointList[(pi-1+pointList.size()-1)%(pointList.size()-1)], &pointList[pi%(pointList.size()-1)]);
    return !qt.intersects_line(l);
}

void optimizePolygonWithPointsAndSegments(polygon &poly, quadtree &qt, int pi, std::vector<int> &si) {

}

void canBeAdded(polygon &poly, quadtree &qt, int pi, lineseg &seg) {

}