//
// Created by insidiae on 27-5-19.
//

#ifndef GEOMETRY_CONTEST_NODE_H
#define GEOMETRY_CONTEST_NODE_H

#include <vector>

#include "edge.h"

class node {
protected:
    int x;
    int y;
    std::vector<edge*> edges;

public:
    node(){}

    node(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }

    std::vector<edge*> getEdges() {
        return this->edges;
    }

    void addEdge(edge e) {
        this->edges.push_back(&e);
    }

};


#endif //GEOMETRY_CONTEST_NODE_H
