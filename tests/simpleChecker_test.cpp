// Created by joris on 4/25/19.

#include <gtest/gtest.h>
#include "../datastructures/polygon.h"
#include "simpleChecker_test.cpp"


TEST(SimpleCheckerTest, NotSimple) {
    std::vector<vec> points;
    points.emplace_back(vec(10,10));
}

TEST(PolygonTest, Contains) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(10, 20));

    polygon poly(points);
    vec point(14, 14);

    EXPECT_TRUE(poly.contains(point));
}

TEST(PolygonTest, NotContains) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(10, 20));

    polygon poly(points);
    vec point(9, 9);

    EXPECT_FALSE(poly.contains(point));
}

TEST(PolygonTest, ContainsWhenPointOfPolygon) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(10, 20));

    polygon poly(points);
    vec point(10, 10);

    EXPECT_TRUE(poly.contains(point));
}

TEST(PolygonTest, ContainsWhenPointOnEdge) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(10, 20));

    polygon poly(points);
    vec point(11, 10);

    EXPECT_TRUE(poly.contains(point));
}
