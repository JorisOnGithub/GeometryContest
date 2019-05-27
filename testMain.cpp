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
//    srand(time(NULL));
    srand(4);



    vec p0 = vec(0, 0);
    vec p1 = vec(0, 8);
    vec p2 = vec(8, 8);
    vec p3 = vec(8, 0);
    vec p4 = vec(6, 4);

    std::vector<vec> points = {p0, p4, p3, p2, p1, p0};
//    std::vector<vec> points = {p1, p4, p0, p3, p2, p1};
    polygon poly = polygon();
    poly.setPoints(points);

    vec bl = vec(0,0);
    vec tr = vec(10,10);

    quadtree tree = quadtree(&bl, &tr);

    lineseg *l = poly.getEdge(0);
    tree.insert(*l);
    lineseg *l1 = poly.getEdge(1);
    tree.insert(*l1);
    lineseg *l2 = poly.getEdge(2);
    tree.insert(*l2);
    lineseg *l3 = poly.getEdge(3);
    tree.insert(*l3);
    lineseg *l4 = poly.getEdge(4);
    tree.insert(*l4);
    lineseg *l5 = poly.getEdge(5);
    tree.insert(*l5);

    std::cout << "area at the beginning: " << poly.area() << std::endl;

    vector<vec> point = poly.getPoints();

    for (int i = 0; i < 10; i++) {
//        std::cout << "optimize: " << std::endl;
        optimizePolygon(poly, tree, false);
        std::cout << "result of " << i << "th iteration: area: " << poly.area() << ", number of points: " << poly.getSize() <<endl;
        vector<vec> point = poly.getPoints();
        for (int j = 0; j < point.size(); j++)  {
            vec p = point[j];
            if (i >= 7 && i <= 8) {
                std::cout << p.x << " " << p.y << endl;
            }
        }

    }




    return 0;
}