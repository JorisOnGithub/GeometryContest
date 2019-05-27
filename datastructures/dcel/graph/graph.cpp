//
// Created by insidiae on 27-5-19.
//

#include "graph.h"

#include <unordered_set>
#include <unordered_map>

void graph::createDelaunayGraph(std::vector<double> coordinates) {
    delaunator::Delaunator d(coordinates);

    std::unordered_map<std::pair<int, int>, node*> checked;

    for(std::size_t i = 0; i < d.triangles.size(); i+=3) {
        std::pair<int, int> point1 = std::make_pair(d.coords[2 * d.triangles[i]], d.coords[2 * d.triangles[i] + 1]);
        std::pair<int, int> point2 = std::make_pair(d.coords[2 * d.triangles[i + 1]], d.coords[2 * d.triangles[i + 1] + 1]);
        std::pair<int, int> point3 = std::make_pair(d.coords[2 * d.triangles[i + 2]], d.coords[2 * d.triangles[i + 2] + 1]);

        if (!checked.count(point1)) {
            node p1(point1.first, point1.second);
            this->addNode(&p1);
            checked.insert(point1, &p1);
        }

        if (!checked.count(point2)) {
            node p2(point1.first, point1.second);
            this->addNode(&p2);
            checked.insert(point1, &p2);
        }

        if (!checked.count(point3)) {
            node p3(point1.first, point1.second);
            this->addNode(&p3);
            checked.insert(point1, &p3);
        }

        edge e12(checked[point1], checked[point2]);
        edge e21(checked[point2], checked[point1]);

        edge e13(checked[point1], checked[point3]);
        edge e31(checked[point3], checked[point1]);

        edge e23(checked[point2], checked[point3]);
        edge e32(checked[point3], checked[point2]);




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

}
