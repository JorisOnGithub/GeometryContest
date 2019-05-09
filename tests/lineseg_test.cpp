#include <gtest/gtest.h>
#include "../datastructures/lineseg.h"

TEST (LineSegTest, IntersectionNegative) {
    vec p1 = vec(0,0);
    vec p2 = vec(-2, -1);
    vec p3 = vec(-1, 0);
    vec p4 = vec(-1, -3);
    lineseg seg(&p1, &p2);
    lineseg to_intersect(&p3, &p4);
    EXPECT_TRUE(seg.intersects(to_intersect));
}

TEST (LineSegTest, IntersectionWithPointLineChangeToLine) {
    vec p1 = vec(0,0);
    vec p2 = vec(0, -1);
    vec p3 = vec(0, -0.5);
    lineseg seg(&p1, &p2);
    lineseg to_intersect(&p3, &p3);
    EXPECT_TRUE(seg.intersects(to_intersect));
    vec p4 = vec(0, 1);
    vec p5 = vec(0, 2);
    to_intersect.set_a(&p4);
    to_intersect.set_b(&p5);
    EXPECT_FALSE(seg.intersects(to_intersect));
}

TEST (LineSegTest, NoIntersection) {
    vec p1 = vec(0,0);
    vec p2 = vec(0,1);
    vec p3 = vec(0,2);
    vec p4 = vec(0,3);
    lineseg seg(&p1, &p2);
    lineseg to_intersect(&p3, &p4);
    EXPECT_FALSE(seg.intersects(to_intersect));
}

TEST (LineSegTest, Equals) {
    vec p1 = vec(0, 0);
    vec p11 = vec(0, 0);
    vec p2 = vec(1, 1);
    vec p21 = vec(1, 1);
    lineseg seg(&p1, &p2);
    lineseg seg2(&p11, &p21);
    EXPECT_TRUE(seg == seg2);
    seg2.set_a(&p21);
    EXPECT_FALSE(seg == seg2);
}
