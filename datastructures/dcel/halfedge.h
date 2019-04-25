//
// Created by insidiae on 4/22/19.
//

#ifndef GEOMETRY_CONTEST_HALFEDGE_H
#define GEOMETRY_CONTEST_HALFEDGE_H

#include "vertex.h"
#include "face.h"

class halfedge {
protected:
    vertex *target;
    face *face;
    halfedge *twin;
    halfedge *next;
    halfedge *previous;

public:
    // Empty constructor
    halfedge() {}

    // Getters
    vertex getTarget() const {
        return *target;
    }

    face getFace() const {
        return *face;
    }

    halfedge getTwin() const {
        return *twin;
    }

    halfedge getNext() const {
        return *next;
    }

    halfedge* getNextPointer() const {
        return next;
    }

    halfedge getPrevious() const {
        return *previous;
    }

    // Setters
    void setTarget(vertex target) {
        this->target = &target;
    }

    void setFace(face f) {
        this->face = &f;
    }

    void setTwin(halfedge twin) {
        this->twin = &twin;
    }

    void setNext(halfedge next) {
        this->next = &next;
    }

    void setPrevious(halfedge prev) {
        this->previous = &prev;
    }


}


#endif //GEOMETRY_CONTEST_HALFEDGE_H
