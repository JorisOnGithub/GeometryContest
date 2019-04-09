#include "io/reader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "datastructures/polygon.h"
#include "simpleChecker.h"
#include "delaunator.hpp"

using namespace std;

void printEvaluation(polygon &solution) {
    auto area = (long long) solution.area();
    std::cout << "area of input polygon: " << area << std::endl;
    std::cout << "input polygon is " << (solution.isConvex() ? "" : " not ") << "convex" << std::endl;
    std::cout << "input polygon is " << (isSimple(solution) ? "" : " not ") << "simple" << std::endl;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "File not given" << std::endl;
        return 1;
    }

    std::cerr << "starting main program" << std::endl;

    // read input
    reader r;
    r.readInput(argv[1]);
    vector<point> points = r.getPoints();


    // create polygon from input order
    polygon solution(points);
    printEvaluation(solution);

    // create polygon from sorted input
    std::sort(points.begin(), points.end());
    solution.setPoints(points);

    /*
    for (int i = 0; i < points.size(); i++) {
        cout << "point " << i << ": (" << points[i].x << ", " << points[i].y << ")" << endl;
    }
    */

    // create polygon from sorted points
    std::cout << "sorted points on y coordinate" << std::endl;
    printEvaluation(solution);

    std::cout << "running deleunay trangulation" << std::endl;

    // inefficient, but just showing it works ;)
    vector<double> coords {};
    for (int i = 0; i < points.size(); i++) {
        coords.push_back(points[i].x);
        coords.push_back(points[i].y);
    }

    delaunator::Delaunator d(coords);
    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        printf(
            "Triangle points: [[%f, %f], [%f, %f], [%f, %f]]\n",
            d.coords[2 * d.triangles[i]],        //tx0
            d.coords[2 * d.triangles[i] + 1],    //ty0
            d.coords[2 * d.triangles[i + 1]],    //tx1
            d.coords[2 * d.triangles[i + 1] + 1],//ty1
            d.coords[2 * d.triangles[i + 2]],    //tx2
            d.coords[2 * d.triangles[i + 2] + 1] //ty2
        );
    }

    std::cerr << "ending main program" << std::endl;
    return 0;
}
