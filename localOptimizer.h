
#ifndef GEOMETRY_CONTEST_LOCALOPTIMIZER_H
#define GEOMETRY_CONTEST_LOCALOPTIMIZER_H

#include "datastructures/polygon.h"
#include "datastructures/quadtree.h"

void optimizePolygon(polygon &poly, quadtree &qt, bool maximize);

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi, bool maximize);

bool canBeRemoved(polygon &poly, quadtree &qt, int pi);

void optimizePolygonWithPointsAndSegments(polygon &poly, quadtree &qt, vec p, std::vector<int> &si, bool maximize);

bool canBeAdded(polygon &poly, quadtree &qt, vec p, int i);

#endif //GEOMETRY_CONTEST_LOCALOPTIMIZER_H
