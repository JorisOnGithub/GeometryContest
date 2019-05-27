#include "localOptimizer.h"
#include <limits>

void optimizePolygon(polygon &poly, quadtree &qt, bool maximize) {
    optimizePolygonWithPoint(poly, qt, largeRandom(poly.getSize()), maximize);
//    optimizePolygonWithPoint(poly, qt, 4, maximize);

}

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi, bool maximize) {
//    std::cout << pi << std::endl;
    if (!canBeRemoved(poly, qt, pi)) {
        std::cout<< "can't be removed" << std::endl;
        return;
    }

    lineseg l1 = poly.getEdge((pi-1+poly.getSize())%poly.getSize());
    lineseg l2 = poly.getEdge((pi+1)%poly.getSize());
    qt.remove(l1);
    qt.remove(l2);
    vec p = poly.getPoint(pi);
    poly.removePoint(pi);
    maximize = (maximize^poly.contains(p));
    lineseg l3 = poly.getEdge((pi-1+poly.getSize())%poly.getSize());
    qt.insert(l3);

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
    double bestArea;
    if (maximize) {
        bestArea = 0;
    } else {
        bestArea = std::numeric_limits<double>::infinity();
    }
    for (int i : si) {
        double area = std::abs((p-poly.getPoint(i)).cross(p-poly.getPoint(i+1))/2);
        if ((maximize ^ (area < bestArea)) && canBeAdded(poly, qt, p, i)) {
            bestArea = area;
            bestI = i;
        }
    }

    lineseg l = poly.getEdge((bestI+poly.getSize())%poly.getSize());

//    std::cout << "remove: " << (*l).a.x << " " << (*l).a.y << ", " << (*l).b.x << " " << (*l).b.y << std::endl;
    qt.remove(l);

    poly.addPoint(p, bestI+1);

    lineseg l1 = poly.getEdge((bestI + poly.getSize())%poly.getSize());
    qt.insert(l1);
    lineseg l2 = poly.getEdge((bestI + 1+poly.getSize())%poly.getSize());
    qt.insert(l2);

//    std::cout << "add: " << (*l1).a.x << " " << (*l1).a.y << ", " << (*l1).b.x << " " << (*l1).b.y << std::endl;
//    std::cout << "add: " << (*l2).a.x << " " << (*l2).a.y << ", " << (*l2).b.x << " " << (*l2).b.y << std::endl;

}

bool canBeAdded(polygon &poly, quadtree &qt, vec p, int i) {
    vec p1 = poly.getPoint(i);
    vec p2 = poly.getPoint((i+1));
    lineseg l1 = lineseg(&p, &p1);
    lineseg l2 = lineseg(&p, &p2);\
    return !(qt.intersects_line(l1) || qt.intersects_line(l2));
}

long long largeRandom(long long mod) {
    long long res = 0;
    for (int i = 0; i < 6; i++) {
        res *= RAND_MAX;
        res += rand();
    }
    return ((res%mod)+mod)%mod;
}