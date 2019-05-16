//
// Created by Hidde Koerts on 4/22/19.
//

#ifndef GEOMETRY_CONTEST_DCEL_H
#define GEOMETRY_CONTEST_DCEL_H

#include <cmath>
#include <list>

#include "vertex.h"
#include "halfedge.h"
#include "face.h"

// Doubly-Connected Edge List datastructure
class dcel {
protected:
    std::list<vertex*> vertices;
    std::list<halfedge*> edges;
    std::list<face*> faces;

public:
    // empty constructor
    dcel(){}

    // constructor from previous structure
    dcel(const std::list<vertex*> v, const std::list<halfedge*> h, const std::list<face*> f) {
        this->vertices = v;
        this->edges = h;
        this->faces = f;
    }

    // Getters
    std::list<vertex*> getVertices() const;
    std::list<halfedge*> getEdges() const;
    std::list<face*> getFaces() const;

    // Add initial 2 vertices, constructing outer face
    void initialVertices(vertex *v1, vertex *v2);

    // Add edge between vertex v and h.target, where h.face is split
    void addEdgeAt(vertex *v, halfedge *h);

    // Insert new vertex connected with a new edge to h.target - ensure correct edge chosen in regard to face!
    void addVertexAt(vertex *v, halfedge *h);

    // Remove edge between vertex v1 and vertex v2
    void removeEdge(vertex *v1, vertex *v2);

    // TODO is it necessary to be able to remove vertices?


    // Flip edge h
    void flipEdge(halfedge *h);

};



#endif //GEOMETRY_CONTEST_DCEL_H
