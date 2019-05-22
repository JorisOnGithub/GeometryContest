#include <gtest/gtest.h>
#include "../datastructures/convexhull.h"
#include "../datastructures/vec.h"
#include "../datastructures/polygon.h"

TEST(ConvexHullTest, AddPointExtendHull) {
    std::vector<vec> points;

    points.emplace_back(vec(0, 0));
    points.emplace_back(vec(3, -1));
    points.emplace_back(vec(4, 5));
    points.emplace_back(vec(-1, 4));

    polygon poly(points);
    convexhull hull(poly);
    vec np(100,100);
    hull.add(np);

    polygon p = hull.getPoly();
    EXPECT_EQ(p.getPoints().size(), 4);

    vec cmp = p.getPoints()[3];
    EXPECT_EQ(cmp.x, np.x);
    EXPECT_EQ(cmp.y, np.y);
}

TEST(ConvexHullTest, AddPointInsideHull) {
    std::vector<vec> points;

    points.emplace_back(vec(0, 0));
    points.emplace_back(vec(3, -1));
    points.emplace_back(vec(4, 5));
    points.emplace_back(vec(-1, 4));

    polygon poly(points);
    convexhull hull(poly);
    vec np(1,1);
    hull.add(np);

    polygon p = hull.getPoly();
    EXPECT_EQ(p.getPoints().size(), 4);

    for (auto v : p.getPoints()) {
        EXPECT_FALSE(v.x == np.x && v.y == np.y);
    }
}
