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

bool checkQuadtree(polygon poly, quadtree tree) {
    set<lineseg> segs = tree.get_all_data();

    if (segs.size() != poly.getSize()) {
        std::cout << "there is a problem: " << segs.size() << " " << poly.getSize() << std::endl;
        return false;
    }



    return true;
}


int mainTest() {
    srand(time(NULL));
//    srand(4);



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
        std::cout << (l).a.x << " " << (l).a.y << ", " << (l).b.x << " " << (l).b.y << std::endl;


    std::set<lineseg> segs = tree.get_all_data();
    std::cout << "segments in tree: " << std::endl;
    for (lineseg l : segs) {
        std::cout << (l).a.x << " " << (l).a.y << ", " << (l).b.x << " " << (l).b.y << std::endl;
    }

    std::cout << "area at the beginning: " << poly.area() << std::endl;

    vector<vec> point = poly.getPoints();

    for (int i = 0; i < 10; i++) {
//        std::cout << "optimize: " << std::endl;
        optimizePolygon(poly, tree, false);
        std::cout << "result of " << i << "th iteration: area: " << poly.area() << ", number of points: " << poly.getSize() <<endl;
        vector<vec> point = poly.getPoints();
        for (int j = 0; j < point.size(); j++)  {
            vec p = point[j];
            if (true) {
                std::cout << p.x << " " << p.y << endl;
            }

        }
        std::set<lineseg> segs = tree.get_all_data();
        std::cout << "segments in tree: " << std::endl;
        for (lineseg l : segs) {
            std::cout << (l).a.x << " " << (l).a.y << ", " << (l).b.x << " " << (l).b.y << std::endl;
        }

        if (!checkQuadtree(poly, tree)) {
            std::cout << "there is a problem in the quad tree" << std::endl;
            //break;
        }

    }




    return 0;
}



