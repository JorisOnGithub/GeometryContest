#include "io/reader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "datastructures/polygon.h"
#include "simpleChecker.h"
#include "delaunator.hpp"
#include "localOptimizer.h"
#include "io/visualiser.h"

using namespace std;

int mainTest() {
    srand(time(NULL));
    vec p0 = vec(0, 0);
    vec p1 = vec(0, 8);
    vec p2 = vec(8, 8);
    vec p3 = vec(8, 0);
    vec p4 = vec(6, 4);

    std::vector<vec> points = {p0, p4, p1, p2, p3, p0};

    polygon poly = polygon();
    poly.setPoints(points);

    std::cout << poly.area() << endl;
    vec bl = vec(0,0);
    vec tr = vec(10,10);

    quadtree tree = quadtree(&bl, &tr);

    lineseg l = poly.getEdge(0);
    tree.insert(l);
    lineseg l1 = poly.getEdge(1);
    tree.insert(l1);
    lineseg l2 = poly.getEdge(2);
    tree.insert(l2);
    lineseg l3 = poly.getEdge(3);
    tree.insert(l3);
    lineseg l4 = poly.getEdge(4);
    tree.insert(l4);
    lineseg l5 = poly.getEdge(5);
    tree.insert(l5);

    vector<vec> point = poly.getPoints();

    for (int i = 0; i < 1; i++) {
        optimizePolygon(poly, tree, false);
        std::cout << "result of " << i << "th iteration: area: " << poly.area() << ", number of points: " << poly.getSize() <<endl;
        vector<vec> point = poly.getPoints();
        for (int i = 0; i < point.size(); i++)  {
            vec p = point[i];
//            std::cout << p.x << " " << p.y << endl;
        }

    }




    return 0;
}