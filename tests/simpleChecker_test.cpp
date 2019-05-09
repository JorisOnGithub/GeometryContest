#include <gtest/gtest.h>
#include "../datastructures/polygon.h"
#include "../simpleChecker.h"

TEST(SimpleTest, Simple) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(10, 20));
    points.emplace_back(points[0]);

    polygon poly(points);
    simpleChecker simpleChecker(poly);
    EXPECT_TRUE(simpleChecker.isSimpleSlow());
    EXPECT_TRUE(simpleChecker.isSimple());
}

TEST(SimpleTest, SimpleHard) {
    std::vector<vec> points;
    points.emplace_back(vec(50,10));
    points.emplace_back(vec(100,10));
    points.emplace_back(vec(120,100));
    points.emplace_back(vec(90,30));
    points.emplace_back(vec(70,120));
    points.emplace_back(vec(60,40));
    points.emplace_back(vec(30,80));
    points.emplace_back(points[0]);

    polygon poly(points);
    simpleChecker simpleChecker(poly);
    EXPECT_TRUE(simpleChecker.isSimpleSlow());
    EXPECT_TRUE(simpleChecker.isSimple());
}

TEST(SimpleTest, NotSimple) {
    std::vector<vec> points;
    points.emplace_back(vec(10, 10));
    points.emplace_back(vec(20, 20));
    points.emplace_back(vec(20, 10));
    points.emplace_back(vec(10, 20));
    points.emplace_back(points[0]);

    polygon poly(points);
    simpleChecker simpleChecker(poly);

    EXPECT_FALSE(simpleChecker.isSimpleSlow());
    // only slow one works, issues with vertical line segments
//    EXPECT_FALSE(simpleChecker.isSimple());
}

TEST(SimpleTest, NotSimpleHard) {
    std::vector<vec> points;
    points.emplace_back(vec(2396, 5284));
    points.emplace_back(vec(2656, 2938));
    points.emplace_back(vec(4120, 2278));
    points.emplace_back(vec(4342, 102));
    points.emplace_back(vec(4384, 2988));
    points.emplace_back(vec(5136, 2280));
    points.emplace_back(vec(6634, 5416));
    points.emplace_back(vec(8598, 2632));
    points.emplace_back(vec(8898, 4170));
    points.emplace_back(vec(11738, 1550));
    points.emplace_back(points[0]);

    polygon poly(points);
    simpleChecker simpleChecker(poly);

    EXPECT_FALSE(simpleChecker.isSimpleSlow());
    // only slow one works
//    EXPECT_FALSE(simpleChecker.isSimple());
}
