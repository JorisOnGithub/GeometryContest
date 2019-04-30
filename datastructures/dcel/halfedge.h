//
// Created by insidiae on 4/22/19.
//

#ifndef GEOMETRY_CONTEST_HALFEDGE_H
#define GEOMETRY_CONTEST_HALFEDGE_H

//#include "vertex.h"
//#include "face.h"
class face;
class vertex;

class halfedge {
protected:
    vertex *target;
    face *facer;
    halfedge *twin;
    halfedge *next;
    halfedge *previous;

public:
    // Empty constructor
    halfedge() {}

    // Getters
    vertex* getTargetPointer() const {
        return target;
    }

    face* getFacePointer() const {
        return facer;
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
    void setTarget(vertex *target) {
        this->target = target;
    }

    void setFace(face *f) {
        this->facer = f;
    }

    void setTwin(halfedge *twin) {
        this->twin = twin;
    }

    void setNext(halfedge *next) {
        this->next = next;
    }

    void setPrevious(halfedge *prev) {
        this->previous = prev;
    }

    bool operator== (const halfedge &h) const {
        return (this == &h);
    }

    bool operator!= (const halfedge &h) const {
        return (this != &h);
    }
};


#endif //GEOMETRY_CONTEST_HALFEDGE_H
