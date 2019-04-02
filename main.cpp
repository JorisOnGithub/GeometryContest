#include "reader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "datastructures/polygon.h"
#include "simpleChecker.h"

using namespace std;

void printEvaluation(polygon &solution) {
    auto area = (long long) solution.area();
    std::cout << "area of input polygon: " << area << std::endl;
    std::cout << "input polygon is " << (solution.isConvex() ? "" : " not ") << "convex" << std::endl;
    std::cout << "input polygon is " << (isSimple(solution) ? "" : " not ") << "simple" << std::endl;
}

int main() {
    std::cerr << "starting main program" << std::endl;

    // read input
    reader r;
    r.readInput("test.txt");
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

    std::cerr << "ending main program" << std::endl;
    return 0;
}