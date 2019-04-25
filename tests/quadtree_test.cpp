#include <gtest/gtest.h>
#include "../datastructures/quadtree.h"

TEST (QuadTreeTest, PointBoundary) {
    vec bl(0, 0);
    vec tr(500, 500);
    vec p1(1, 1);
    vec p2(300, 200);
    vec p3(800, 500);
    vec p4(-50, -10);
    std::cout<<"CREATING TREE"<<std::endl;
    std::cout<<&bl<<std::endl;
    std::cout<<&tr<<std::endl;
    quadtree t(&bl, &tr);
    std::cout<<"TREE CREATED"<<std::endl;
    std::cout<<t.botleft<<std::endl;
    std::cout<<t.topright<<std::endl;
    EXPECT_TRUE(t.in_boundary(p1));
    EXPECT_TRUE(t.in_boundary(p2));
    EXPECT_FALSE(t.in_boundary(p3));
    EXPECT_FALSE(t.in_boundary(p4));
    vec bl1(-300, -300);
    vec tr1(300, 150);
    std::cout<<"CREATING TREE"<<std::endl;
    quadtree t1(&bl1, &tr1);
    EXPECT_TRUE(t.in_boundary(p1));
    EXPECT_TRUE(t.in_boundary(p3));
    EXPECT_FALSE(t.in_boundary(p3));
    EXPECT_FALSE(t.in_boundary(p2));
}
//TEST (QuadTreeTest, PointOnBoundary) {
//    vec bl(0, 0);
//    vec tr(300, 300);
//    quadtree t(&bl, &tr);
//    vec p1(0, 0);
//    vec p2(0, 50);
//    vec p3(0, 301);
//    vec p4(300, 300);
//    EXPECT_TRUE(t.in_boundary(p1));
//    EXPECT_TRUE(t.in_boundary(p2));
//    EXPECT_TRUE(t.in_boundary(p4));
//    EXPECT_FALSE(t.in_boundary(p3));
//}
//TEST (QuadTreeTest, LineInBoundary) {
//    vec bl(0, 0);
//    vec tr(300, 300);
//    quadtree t(&bl, &tr);
//    lineseg boundry(&bl, &tr);
//    EXPECT_TRUE(t.in_boundary(boundry));
//    vec newA(50, 50);
//    boundry.set_a(&newA);
//    EXPECT_TRUE(t.in_boundary(boundry));
//    vec bl1(-50, -50);
//    vec tr1(50, 50);
//    quadtree t1(&bl1, &tr1);
//    EXPECT_FALSE(t.in_boundary(boundry));
//    boundry.set_b(&bl1);
//    EXPECT_TRUE(t.in_boundary(boundry));
//    boundry.set_a(&bl);
//    EXPECT_TRUE(t.in_boundary(boundry));
//}
//TEST (QuadTreeTest, LineIntersectBoundary) {
//    vec bl(-10, -10);
//    vec tr(10, 10);
//    quadtree t(&bl, &tr);
//    vec a(9, 9);
//    vec b(10, 100);
//    lineseg l(&a, &b);
//    EXPECT_TRUE(t.intersects_boundary(l));
//    vec newA(50, 50);
//    l.set_a(&newA);
//    EXPECT_FALSE(t.intersects_boundary(l));
//}
//TEST (QuadTreeTest, LineOnBoundary) {
//    vec bl(0, 0);
//    vec tr(10, 10);
//    quadtree t(&bl, &tr);
//    vec a(0, 1);
//    vec b(0, 5);
//    lineseg l(&a, &b);
//    EXPECT_TRUE(t.intersects_boundary(l));
//    vec newB(0, 100);
//    l.set_b(&newB);
//    EXPECT_TRUE(t.intersects_boundary(l));
//    vec newA(0, 11);
//    l.set_a(&newA);
//    EXPECT_FALSE(t.intersects_boundary(l));
//}
