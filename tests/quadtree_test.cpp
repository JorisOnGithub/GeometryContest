#include <gtest/gtest.h>
#include "../datastructures/quadtree.h"

TEST (QuadTreeTest, PointBoundary) {
    vec bl(0, 0);
    vec tr(500, 500);
    vec p1(1, 1);
    vec p2(300, 200);
    vec p3(800, 500);
    vec p4(-50, -10);
    quadtree t(&bl, &tr);

    EXPECT_TRUE(t.in_boundary(p1));
    EXPECT_TRUE(t.in_boundary(p2));
    EXPECT_FALSE(t.in_boundary(p3));
    EXPECT_FALSE(t.in_boundary(p4));
    vec bl1(-300, -300);
    vec tr1(300, 150);

    quadtree t1(&bl1, &tr1);
    EXPECT_TRUE(t1.in_boundary(p1));
    EXPECT_TRUE(t1.in_boundary(p4));
    EXPECT_FALSE(t1.in_boundary(p3));
    EXPECT_FALSE(t1.in_boundary(p2));
}
TEST (QuadTreeTest, PointOnBoundary) {
    vec bl(0, 0);
    vec tr(300, 300);
    quadtree t(&bl, &tr);
    vec p1(0, 0);
    vec p2(0, 50);
    vec p3(0, 301);
    vec p4(300, 300);
    EXPECT_TRUE(t.in_boundary(p1));
    EXPECT_TRUE(t.in_boundary(p2));
    EXPECT_TRUE(t.in_boundary(p4));
    EXPECT_FALSE(t.in_boundary(p3));
}
TEST (QuadTreeTest, LineInBoundary) {
    vec bl(0, 0);
    vec tr(300, 300);
    quadtree t(&bl, &tr);
    lineseg boundry(&bl, &tr);
    EXPECT_TRUE(t.in_boundary(boundry));
    vec newA(50, 50);
    boundry.set_a(&newA);
    EXPECT_TRUE(t.in_boundary(boundry));
    vec bl1(-50, -50);
    vec tr1(50, 50);
    quadtree t1(&bl1, &tr1);
    EXPECT_FALSE(t1.in_boundary(boundry));
    boundry.set_b(&bl1);
    EXPECT_TRUE(t1.in_boundary(boundry));
    boundry.set_a(&bl);
    EXPECT_TRUE(t1.in_boundary(boundry));
}
TEST (QuadTreeTest, LineIntersectBoundary) {
    vec bl(-10, -10);
    vec tr(10, 10);
    quadtree t(&bl, &tr);
    vec a(9, 9);
    vec b(10, 100);
    lineseg l(&a, &b);
    EXPECT_TRUE(t.intersects_boundary(l));
    vec newA(50, 50);
    l.set_a(&newA);
    EXPECT_FALSE(t.intersects_boundary(l));
}
TEST (QuadTreeTest, LineOnBoundary) {
    vec bl(0, 0);
    vec tr(10, 10);
    quadtree t(&bl, &tr);
    vec a(0, 1);
    vec b(0, 5);
    lineseg l(&a, &b);
    EXPECT_TRUE(t.intersects_boundary(l));
    vec newB(0, 100);
    l.set_b(&newB);
    EXPECT_TRUE(t.intersects_boundary(l));
    vec newA(0, 11);
    l.set_a(&newA);
    EXPECT_FALSE(t.intersects_boundary(l));
}
TEST(QuadTreeTest, InsertRemove) {
    vec bl(0, 0);
    vec tr(50, 50);
    quadtree t(&bl, &tr);
    vec a(1, 1);
    vec b(20, 20);
    lineseg l(&a, &b);
    EXPECT_TRUE(t.insert(l));
    EXPECT_TRUE(t.size() == 1); 
    vec c(22, 22);
    vec d(35, 45);
    lineseg l1(&c, &d);
    EXPECT_FALSE(t.remove(l1));
    EXPECT_TRUE(t.insert(l1));
    EXPECT_TRUE(t.size() == 2);
    EXPECT_TRUE(t.remove(l));
    EXPECT_TRUE(t.size() == 1);
    EXPECT_FALSE(t.remove(l));
    EXPECT_TRUE(t.size() == 1);
    EXPECT_TRUE(t.is_leaf());
    vec e(-5, -100); 
    vec f(0, -1); 
    lineseg l3(&e, &f);
    EXPECT_FALSE(t.insert(l3));
}
TEST (QuadTreeTest, QuadLineInteresection) {
    vec bl(0, 0);
    vec tr(50, 50);
    quadtree t(&bl, &tr);
    vec a(10, 10);
    vec b(10, 15);
    lineseg l1(&a, &b);
    vec c(9, 13);
    vec d(12, 13);
    lineseg l2(&c, &d);
    vec e(12, 10);
    vec f(12, 5);
    lineseg l3(&e, &f);
    vec g(1, 1);
    vec h(2, 2);
    lineseg l4(&g, &h);
    EXPECT_TRUE(t.insert(l1));
    EXPECT_TRUE(t.insert(l2));
    EXPECT_TRUE(t.insert(l3));
    EXPECT_TRUE(t.insert(l4));
    EXPECT_TRUE(t.intersects_line(l1));
    EXPECT_TRUE(t.intersects_line(l2));
    EXPECT_FALSE(t.intersects_line(l3));
    EXPECT_FALSE(t.intersects_line(l4));
    vec l(40, 40);
    vec p(40, 45);
    lineseg l5(&l, &p);
    EXPECT_TRUE(t.insert(l5));
    vec aa(30, 39);
    vec bb(35, 39);
    lineseg l6(&aa, &bb);
    std::cout<<t.size()<<std::endl;
    EXPECT_TRUE(t.insert(l6));
    EXPECT_FALSE(t.is_leaf());
    std::cout<<t.size()<<std::endl;
    EXPECT_TRUE(t.intersects_line(l1));
    EXPECT_TRUE(t.intersects_line(l2));
    EXPECT_FALSE(t.intersects_line(l3));
    EXPECT_FALSE(t.intersects_line(l4));
    EXPECT_FALSE(t.intersects_line(l5));
}
