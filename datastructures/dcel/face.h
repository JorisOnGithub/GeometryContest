//
// Created by insidiae on 4/22/19.
//

#ifndef GEOMETRY_CONTEST_FACE_H
#define GEOMETRY_CONTEST_FACE_H

#include <vector>
#include <set>
#include <unordered_set>

#include "halfedge.h"

class face {
protected:
    halfedge *edge;

public:
    // empty constructor
    face(){}

    // Getter
    halfedge* getEdgePointer() const {
        return edge;
    }

    // Setter
    void setEdge(halfedge *edge) {
        this->edge = edge;
    }

    // Return all halfedges adjacent to face
    std::vector<halfedge> getAdjacentEdges() const;

    // Return all adjacent faces
    std::unordered_set<face*> getAdjacentFacesPointers() const;

    bool operator== (const face &f) const {
        return (this == &f);
    }
};


#endif //GEOMETRY_CONTEST_FACE_H
