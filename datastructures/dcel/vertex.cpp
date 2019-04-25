//
// Created by insidiae on 4/22/19.
//

#include "vertex.h"

std::list<halfedge> vertex::getEdges() const {
    return this->edges;
}

void vertex::addEdge(halfedge h) {
    this->edges.push_back(h);
}
