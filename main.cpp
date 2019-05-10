#include "io/reader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "datastructures/polygon.h"
#include "simpleChecker.h"
#include "delaunator.hpp"
#include "localOptimizer.h"
#include "solutionMaker.h"
#include "io/visualiser.h"
#include "testMain.h"

using namespace std;

void printEvaluation(polygon &solution) {
    auto area = (long long) solution.area();
    std::cout << "area of input polygon: " << area << std::endl;
    std::cout << "input polygon is " << (solution.isConvex() ? "" : " not ") << "convex" << std::endl;
    std::cout << "input polygon is " << (isSimple(solution) ? "" : " not ") << "simple" << std::endl;
}

int main(int argc, char **argv) {
    mainTest();
//    if (argc < 2) {
//        std::cerr << "File not given" << std::endl;
//        return 1;
//    }
//
//    std::cerr << "starting main program" << std::endl;
//
//    // read input
//    reader r;
//    r.readInput(argv[1]);
//    vector<vec> points = r.getPoints();
//    points.emplace_back(points[0]);
//
//    // create polygon from input order
//    polygon solution(points);
//    printEvaluation(solution);
//
//    // create polygon from sorted input
////    std::sort(points.begin(), points.end());
////    solution.setPoints(points);
//
//    /*
//    for (int i = 0; i < points.size(); i++) {
//        cout << "point " << i << ": (" << points[i].x << ", " << points[i].y << ")" << endl;
//    }
//     */
//
//    // create polygon from sorted points
////    std::cout << "sorted points on y coordinate" << std::endl;
////    printEvaluation(solution);
//
//
//    /*
//    std::cout << "running delaunay trangulation" << std::endl;
//
//    // inefficient, but just showing it works ;)
//    vector<double> coords{};
//    for (int i = 0; i < points.size(); i++) {
//        coords.push_back(points[i].x);
//        coords.push_back(points[i].y);
//    }
//
//    delaunator::Delaunator d(coords);
//
//    vector<triangle> triangles{};
//
//    for (std::size_t i = 0; i < d.triangles.size(); i += 3) {
//        vec p1(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]);
//        vec p2(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]);
//        vec p3(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]);
//
//        triangle t(p1, p2, p3);
//        triangles.emplace_back(t);
//
//        printf(
//                "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
//                d.coords[2 * d.triangles[i]],        //tx0
//                d.coords[2 * d.triangles[i] + 1],    //ty0
//                d.coords[2 * d.triangles[i + 1]],    //tx1
//                d.coords[2 * d.triangles[i + 1] + 1],//ty1
//                d.coords[2 * d.triangles[i + 2]],    //tx2
//                d.coords[2 * d.triangles[i + 2] + 1] //ty2
//        );
//    }
//     */
//    std::cout << "finding solution" << std::endl;
////    solutionMaker sm = solutionMaker(triangles);
////    polygon poly = sm.getSolution();
//    solutionMaker sm = solutionMaker(points);
//    polygon poly = sm.getSolution();
//    printEvaluation(poly);
//
//    std::cout << "done finding solution" << std::endl;
//    // run visualiser
//    std::cout << "running visualiser" << std::endl;
//    visualiser v;
//    try {
//        v.visualise(points, poly, argv[1]);
//    } catch (const char *e) {
//        std::cerr << e << std::endl;
//    }
//
//    std::cerr << "ending main program" << std::endl;
    return 0;
}
