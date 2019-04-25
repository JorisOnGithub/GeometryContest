//
// Created by insidiae on 4/22/19.
//

#include "face.h"

std::vector<halfedge> face::getAdjacentEdges() const {
    std::vector<halfedge> adjacentEdges;
    halfedge *pointer = this->edge;

    do {
        adjacentEdges.push_back(*pointer);
        pointer = (*pointer).getNextPointer();
    } while (pointer != this->edge);

    return adjacentEdges;
}

std::set<face> face::getAdjacentFaces() const {
    std::set<face> adjacentFaces;
    std::vector<halfedge> adjacentEdges = this->getAdjacentEdges();

    for (halfedge e : adjacentEdges) {
        adjacentFaces.insert(e.getFace());
    }

    return adjacentFaces;
}
