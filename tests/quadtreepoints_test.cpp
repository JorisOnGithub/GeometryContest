#include <gtest/gtest.h>
#include "../datastructures/quadtreepoints.h"

TEST (QuadtreePoints, InsertRemove) {
    // boundary
    vec bl(0, 0);
    vec tr(100, 100);
    // points
    vec a(0, 1);
    vec b(10, 10);
    vec c(100, 100);
    vec d(0, -1);
    vec e(101, 101);
    vec f(50, 80);
    vec g(60, 70);
    
    quadtreeP t(&bl, &tr);

    EXPECT_TRUE(t.insert(a));
    EXPECT_TRUE(t.insert(b));
    EXPECT_TRUE(t.insert(c));
    EXPECT_TRUE(t.insert(f));
    EXPECT_TRUE(t.insert(g));
    
    EXPECT_FALSE(t.insert(d));
    EXPECT_FALSE(t.insert(e));

    EXPECT_TRUE(t.size() == 5);
    
    vec l(30, 30);
    EXPECT_FALSE(t.remove(l));
    EXPECT_FALSE(t.remove(d));
    EXPECT_FALSE(t.remove(e));

    EXPECT_TRUE(t.size() == 5);

    EXPECT_TRUE(t.remove(a));
    EXPECT_TRUE(t.size() == 4);
    EXPECT_TRUE(t.remove(b));
    EXPECT_TRUE(t.size() == 3);
    EXPECT_TRUE(t.remove(c));
    EXPECT_TRUE(t.size() == 2);
    EXPECT_TRUE(t.remove(f));
    EXPECT_TRUE(t.size() == 1);
    EXPECT_TRUE(t.remove(g));

    EXPECT_TRUE(t.size() == 0);
}

TEST(QuadtreePoints, RangeSearch) {
    // boundary
    vec bl(0, 0);
    vec tr(100, 100);
    // points
    vec a(0, 1);
    vec b(10, 10);
    vec c(100, 100);
    vec d(30, 30);
    vec e(10, 20);
    vec f(50, 80);
    vec g(60, 70);

    quadtreeP t(&bl, &tr);


}
