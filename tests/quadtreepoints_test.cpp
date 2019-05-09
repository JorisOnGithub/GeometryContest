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

    EXPECT_TRUE(t.insert(a));
    EXPECT_TRUE(t.insert(b));
    EXPECT_TRUE(t.insert(c));
    EXPECT_TRUE(t.insert(d));
    EXPECT_TRUE(t.insert(e));
    EXPECT_TRUE(t.insert(f));
    EXPECT_TRUE(t.insert(g));
   
    vec rbl(0, 0);
    vec rtr(100, 100);
    std::set<vec*> r1 = t.range_search(rbl, rtr);
    EXPECT_TRUE(r1.size() == t.size());

    vec rbl1(25, 25);
    vec rtr1(40, 40);
    std::set<vec*> r2 = t.range_search(rbl1, rtr1);
    EXPECT_TRUE(r2.size() == 1);
    EXPECT_TRUE(r2.find(&d) != r2.end());

    vec rbl2(25, 25);
    vec rtr2(29, 29);
    std::set<vec*> r3 = t.range_search(rbl2, rtr2);
    EXPECT_TRUE(r3.size() == 0);

    vec rbl3(29, 29);
    vec rtr3(80, 95);
    std::set<vec*> r4 = t.range_search(rbl3, rtr3);
    EXPECT_TRUE(r4.size() == 3);
    EXPECT_TRUE(r4.find(&d) != r4.end());
    EXPECT_TRUE(r4.find(&g) != r4.end());
    EXPECT_TRUE(r4.find(&f) != r4.end());
}
