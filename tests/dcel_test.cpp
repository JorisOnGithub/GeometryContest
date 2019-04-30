//
// Created by insidiae on 30-4-19.
//

#include <gtest/gtest.h>
#include "../datastructures/dcel/dcel.h"

TEST (dcel, CheckInitialization) {
    dcel dcel;
    vertex v0(0, 0);
    vertex v1(1, 1);

    dcel.initialVertices(v0, v1);

    ASSERT_EQ(v0.getEdges().front().getTargetPointer(), &v1);
    ASSERT_EQ(v1.getEdges().front().getTargetPointer(), &v0);

    ASSERT_EQ(v0.getEdges().front().getNextPointer(), v0.getEdges().front().getTwinPointer());
    ASSERT_EQ(v1.getEdges().front().getNextPointer(), v1.getEdges().front().getTwinPointer());

}
