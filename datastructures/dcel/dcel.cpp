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

void dcel::addEdgeAt(vertex v, halfedge h) {
    face f = h.getFace();
    face f1;
    face f2;
    halfedge h1;
    halfedge h2;

    h.getTarget().addEdge(h1);
    v.addEdge(h2);

    f1.getEdge(h1);
    f2.setEdge(h2);

    h1.setTwin(h2);
    h2.setTwin(h1);

    h1.setTarget(v);
    h2.setTarget(h.getTarget());

    h2.setNext(h.getNext());
    h2.getNext().setPrevious(h2);
    h1.setPrevious(h);
    h.setNext(h1);

    halfedge *iterator = &h2;

    h2.setFace(f2);
    while (iterator->getTarget() != v) {
        iterator = iterator->getNextPointer();
        iterator->setFace(f2);
    }

    h1.setNext(iterator->getNext());
    h1.getNext().setPrevious(h1);

    iterator->setNext(h2);
    h2.setPrevious(*iterator);

    iterator = &h1;

    do {
        iterator->setFace(f1);
        iterator = iterator->getNextPointer();
    } while (iterator->getTarget() != h.getTarget());

    this->edges.push_back(h1);
    this->edges.push_back(h2);
    this->faces.push_back(f1);
    this->faces.push_back(f2);

    this->faces.remove(f);
}

void dcel::initialVertices(vertex v1, vertex v2) {
    if(!this->faces.empty()) {
        throw "Non-empty DCEL";
    }
    face outer;
    halfedge h1;
    halfedge h2;

    h1.setFace(outer);
    h2.setFace(outer);

    h1.setTarget(v1);
    h2.setTarget(v2);

    h1.setNext(h2);
    h1.setPrevious(h2);
    h2.setNext(h1);
    h2.setPrevious(h1);

    h1.setTwin(h2);
    h2.setTwin(h1);

    v1.addEdge(h2);
    v2.addEdge(h1);

    outer.setEdge(h1);

    this->vertices.push_back(v1);
    this->vertices.push_back(v2);
    this->faces.push_back(outer);
    this->edges.push_back(h1);
    this->edges.push_back(h2);
}


