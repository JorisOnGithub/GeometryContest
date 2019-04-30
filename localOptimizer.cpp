#include "localOptimizer.h"

void optimizePolygon(polygon &poly, quadtree &qt, bool maximize) {
    optimizePolygonWithPoint(poly, qt, rand()%poly.getSize(), maximize);
}

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi, bool maximize) {
    if (!canBeRemoved(poly, qt, pi)) {
        return;
    }
    qt.remove(poly.getEdge((pi-1+poly.getSize())%poly.getSize()));
    qt.remove(poly.getEdge((pi+1)%poly.getSize()));
    vec p = poly.getPoint(pi);
    poly.removePoint(pi);
    maximize = !(maximize^poly.contains(p));
    qt.insert(poly.getEdge((pi-1+poly.getSize())%poly.getSize()));
    std::vector<int> si = {};
    for (int i = 0; i < 10; i++) {
        si.push_back((pi-5+i+poly.getSize())%poly.getSize());
    }
    optimizePolygonWithPointsAndSegments(poly, qt, p, si, maximize);
}

bool canBeRemoved(polygon &poly, quadtree &qt, int pi) {
    vec p1 = poly.getPoint((pi-1+poly.getSize())%poly.getSize());
    vec p2 = poly.getPoint((pi+1)%poly.getSize());
    lineseg l = lineseg(&p1,&p2);
    return !qt.intersects_line(l);
}

void optimizePolygonWithPointsAndSegments(polygon &poly, quadtree &qt, vec p, std::vector<int> &si, bool maximize) {
    int bestI = 0;
    double bestArea = 0;
    for (int i : si) {
        double area = std::abs((p-poly.getPoint(i)).cross(p-poly.getPoint(i+1))/2);
        if ((maximize ^ (area < bestArea)) && canBeAdded(poly, qt, p, i)) {
            bestArea = area;
            bestI = i;
        }
    }
    poly.addPoint(p, bestI+1);
}

bool canBeAdded(polygon &poly, quadtree &qt, vec p, int i) {
    vec p1 = poly.getPoint(i);
    vec p2 = poly.getPoint((i+1)%poly.getSize());
    lineseg l1 = lineseg(&p, &p1);
    lineseg l2 = lineseg(&p, &p2);
    return !(qt.intersects_line(l1) || qt.intersects_line(l2));
}