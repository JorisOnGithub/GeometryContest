
#ifndef GEOMETRY_CONTEST_LOCALOPTIMIZER_H
#define GEOMETRY_CONTEST_LOCALOPTIMIZER_H

#include "datastructures/polygon.h"
#include "datastructures/quadtree.h"

void optimizePolygon(polygon &poly, quadtree &qt);

void optimizePolygonWithPoint(polygon &poly, quadtree &qt, int pi);

bool canBeRemoved(polygon &poly, quadtree &qt, int pi);

void optimizePolygonWithPointsAndSegments(polygon &poly, quadtree &qt, int pi, std::vector<lineseg> &segments);

void canBeAdded(polygon &poly, quadtree &qt, int &pi, lineseg &seg);

#endif //GEOMETRY_CONTEST_LOCALOPTIMIZER_H
