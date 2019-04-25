#include "localOptimizer.h"

void optimizePolygon(polygon &poly, quadtree &qt) {
    optimizePolygonWithPoint(poly, qt, 0);

}

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi) {
    if (!canBeRemoved(poly, qt, pi)) {
        return;
    }

}

bool canBeRemoved(polygon &poly, quadtree &qt, int pi) {

}

void optimizePolygonWithPointsAndSegments(polygon &poly, quadtree &qt, point &p, vector<lineseg> &segments) {

}

void canBeAdded(polygon &poly, quadtree &qt, point &p, lineseg &seg) {

}