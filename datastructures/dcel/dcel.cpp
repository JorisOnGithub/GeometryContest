//
// Created by insidiae on 4/22/19.
//

#include "dcel.h"


std::list<vertex> dcel::getVertices() const {
    return this->vertices;
}

std::list<halfedge> dcel::getEdges() const {
    return this->edges;
}

std::list<face> dcel::getFaces() const {
    return this->faces;
}

