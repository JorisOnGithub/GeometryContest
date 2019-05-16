//
// Created by insidiae on 30-4-19.
//

#include <gtest/gtest.h>
#include "../datastructures/dcel/dcel.h"

TEST (dcel, CheckInitialization) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(1, 1);

    dcel.initialVertices(&v0, &v1);

    ASSERT_EQ(v0.getEdges().size(), 1);
    ASSERT_EQ(v1.getEdges().size(), 1);

    ASSERT_EQ(v0.getEdges().front()->getTargetPointer(), &v1);
    ASSERT_EQ(v1.getEdges().front()->getTargetPointer(), &v0);

    ASSERT_EQ(v0.getEdges().front()->getNextPointer(), v0.getEdges().front()->getTwinPointer());
    ASSERT_EQ(v1.getEdges().front()->getNextPointer(), v1.getEdges().front()->getTwinPointer());

    ASSERT_EQ(&v0, dcel.getVertices().front());
    ASSERT_EQ(&v1, dcel.getVertices().back());

    ASSERT_EQ(dcel.getEdges().size(), 2);
    ASSERT_EQ(dcel.getVertices().size(), 2);
    ASSERT_EQ(dcel.getFaces().size(), 1);
}

TEST (dcel, CheckAddVertexAt) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(0, 1);
    vertex v2(1, 0);

    dcel.initialVertices(&v0, &v1);

    dcel.addVertexAt(&v2, v1.getEdges().front());

    ASSERT_EQ(v0.getEdges().front()->getFacePointer(), v2.getEdges().front()->getFacePointer());
    ASSERT_EQ(v1.getEdges().front()->getFacePointer(), v2.getEdges().front()->getFacePointer());

    ASSERT_EQ(v2.getEdges().front()->getTargetPointer(), &v0);
    ASSERT_EQ(v0.getEdges().back()->getTargetPointer(), &v2);

    ASSERT_EQ(v2.getEdges().front()->getNextPointer()->getTargetPointer(), &v1);
    ASSERT_EQ(v2.getEdges().front()->getTwinPointer()->getTargetPointer(), &v2);

    ASSERT_EQ(dcel.getEdges().size(), 4);
    ASSERT_EQ(dcel.getFaces().size(), 1);
    ASSERT_EQ(dcel.getVertices().size(), 3);
}

TEST (dcel, CheckAddEdgeAt) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(0, 1);
    vertex v2(1, 0);

    dcel.initialVertices(&v0, &v1);
    dcel.addVertexAt(&v2, v1.getEdges().front());

    dcel.addEdgeAt(&v2, v0.getEdges().front());

    ASSERT_FALSE(v0.getEdges().front()->getFacePointer() == v0.getEdges().front()->getTwinPointer()->getFacePointer());
    ASSERT_EQ(v0.getEdges().front()->getNextPointer()->getNextPointer()->getNextPointer(), v0.getEdges().front());
    ASSERT_EQ(v0.getEdges().back()->getNextPointer()->getNextPointer()->getNextPointer(), v0.getEdges().back());

    ASSERT_EQ(dcel.getEdges().size(), 6);
    ASSERT_EQ(dcel.getVertices().size(), 3);
    ASSERT_EQ(dcel.getFaces().size(), 2);
}

TEST (dcel, GeneralTest) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(0, 1);
    vertex v2(1, 0);

    dcel.initialVertices(&v0, &v1);
    dcel.addVertexAt(&v2, v1.getEdges().front());
    dcel.addEdgeAt(&v2, v0.getEdges().front());

    ASSERT_EQ(v0.getEdges().front()->getFacePointer(), v0.getEdges().front()->getNextPointer()->getFacePointer());
    ASSERT_EQ(v0.getEdges().front()->getFacePointer(), v0.getEdges().front()->getNextPointer()->getNextPointer()->getFacePointer());

    ASSERT_EQ(v0.getEdges().front()->getTwinPointer()->getFacePointer(), v0.getEdges().front()->getTwinPointer()->getNextPointer()->getFacePointer());
    ASSERT_EQ(v0.getEdges().front()->getTwinPointer()->getFacePointer(), v0.getEdges().front()->getTwinPointer()->getNextPointer()->getNextPointer()->getFacePointer());

    ASSERT_FALSE(v0.getEdges().front()->getFacePointer() == v0.getEdges().front()->getTwinPointer()->getFacePointer());
}

TEST (dcel, GetAdjacentEdges) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(0, 1);
    vertex v2(1, 0);

    dcel.initialVertices(&v0, &v1);
    dcel.addVertexAt(&v2, v1.getEdges().front());
    dcel.addEdgeAt(&v2, v0.getEdges().front());

    ASSERT_EQ(v0.getEdges().front()->getFacePointer()->getAdjacentEdges().size(), 3);
    ASSERT_EQ(v0.getEdges().back()->getFacePointer()->getAdjacentEdges().size(), 3);
}

TEST (dcel, GetAdjacentFacesPointers) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(0, 1);
    vertex v2(1, 0);

    dcel.initialVertices(&v0, &v1);
    dcel.addVertexAt(&v2, v1.getEdges().front());
    dcel.addEdgeAt(&v2, v0.getEdges().front());

    ASSERT_EQ(v0.getEdges().front()->getFacePointer()->getAdjacentFacesPointers().size(), 1);
    ASSERT_EQ(v0.getEdges().front()->getFacePointer()->getAdjacentFacesPointers().count(v0.getEdges().front()->getTwinPointer()->getFacePointer()), 1);
}