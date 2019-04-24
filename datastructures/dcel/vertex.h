//
// Created by insidiae on 4/22/19.
//

#ifndef GEOMETRY_CONTEST_VERTEX_H
#define GEOMETRY_CONTEST_VERTEX_H

#include <list>

#include "halfedge.h"

class vertex {
protected:
    double x;
    double y;
    std::list<halfedge> edges;

public:
    // empty constructor
    vertex(){}

    // Getters
    std::list<halfedge> getEdges() const;

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    // Setters
    void setX(double x) {
        this->x = x;
    }

    void setY(double y) {
        this->y = y;
    }

    void addEdge(halfedge h);
};


#endif //GEOMETRY_CONTEST_VERTEX_H
