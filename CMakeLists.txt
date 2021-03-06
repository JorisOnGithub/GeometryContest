cmake_minimum_required(VERSION 3.13)
project(Geometry_Contest)

set(CMAKE_CXX_STANDARD 14)

# Google Tests

find_package(GTest)
if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(UnitTest tests/tests.cpp datastructures/vec.h
        datastructures/vec.cpp datastructures/polygon.h
        datastructures/polygon.cpp tests/polygon_test.cpp
        datastructures/lineseg.h datastructures/lineseg.cpp
        tests/lineseg_test.cpp tests/quadtree_test.cpp
        datastructures/quadtree.cpp datastructures/quadtree.h
        tests/simpleChecker_test.cpp simpleChecker.h simpleChecker.cpp
        datastructures/quadtreepoints.cpp datastructures/quadtreepoints.h
        tests/quadtreepoints_test.cpp 
        datastructures/convexhull.h datastructures/convexhull.cpp
        tests/convexhull_test.cpp)
    target_link_libraries(UnitTest ${GTEST_LIBRARIES} pthread)
endif()

# Main
add_executable(Geometry_Contest delaunator.hpp main.cpp io/reader.cpp
    io/reader.h simpleChecker.cpp simpleChecker.h datastructures/vec.cpp
    datastructures/vec.h datastructures/line.cpp datastructures/line.h
    datastructures/polygon.cpp datastructures/polygon.h
    datastructures/quadtree.h datastructures/quadtree.cpp
    datastructures/lineseg.cpp datastructures/lineseg.h
    datastructures/quadtreepoints.cpp datastructures/quadtreepoints.h
    io/visualiser.cpp io/visualiser.h lib/TinyXML2/tinyxml2.h
    lib/TinyXML2/tinyxml2.cpp solutionMaker.h solutionMaker.cpp
    datastructures/convexhull.h datastructures/convexhull.cpp
    NWERC09Jaap.cpp NWERC09Jaap.h
    NWERC09Argafal.cpp NWERC09Argafal.h)
