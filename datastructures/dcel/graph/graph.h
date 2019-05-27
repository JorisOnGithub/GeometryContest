//
// Created by insidiae on 27-5-19.
//

#ifndef GEOMETRY_CONTEST_GRAPH_H
#define GEOMETRY_CONTEST_GRAPH_H

#include <vector>

#include "node.h"
#include "delaunator.hpp"


class graph {
private:
    std::vector<node*> nodes;

public:
    graph(){}

    std::vector<node*> getNodes() {
        return this->nodes;
    }

    void addNode(node* n) {
        this->nodes.push_back(n);
    }

    // creates graph representation of Delaunay triangulation of coordinates given in <x0, y0, x1, y1, ...>
    void createDelaunayGraph(std::vector<double> coordinates);
};


#endif //GEOMETRY_CONTEST_GRAPH_H
