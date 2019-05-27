cmake_minimum_required(VERSION 3.10)
project(Geometry_Contest)

set(CMAKE_CXX_STANDARD 14)

# Google Tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(UnitTest tests/tests.cpp datastructures/vec.h datastructures/vec.cpp datastructures/polygon.h datastructures/polygon.cpp tests/polygon_test.cpp datastructures/lineseg.h datastructures/lineseg.cpp tests/lineseg_test.cpp tests/quadtree_test.cpp datastructures/quadtree.cpp datastructures/quadtree.h tests/dcel_test.cpp datastructures/dcel/dcel.h datastructures/dcel/vertex.cpp datastructures/dcel/vertex.h datastructures/dcel/dcel.cpp datastructures/dcel/halfedge.h datastructures/dcel/halfedge.cpp datastructures/dcel/face.h datastructures/dcel/face.cpp)
target_link_libraries(UnitTest ${GTEST_LIBRARIES} pthread)

# Main
add_executable(Geometry_Contest delaunator.hpp main.cpp io/reader.cpp io/reader.h simpleChecker.cpp simpleChecker.h datastructures/vec.cpp datastructures/vec.h datastructures/line.cpp datastructures/line.h datastructures/polygon.cpp datastructures/polygon.h datastructures/quadtree.h datastructures/quadtree.cpp datastructures/lineseg.cpp datastructures/lineseg.h datastructures/dcel/dcel.h datastructures/dcel/vertex.cpp datastructures/dcel/vertex.h datastructures/dcel/dcel.cpp datastructures/dcel/halfedge.h datastructures/dcel/halfedge.cpp datastructures/dcel/face.h datastructures/dcel/face.cpp io/visualiser.cpp io/visualiser.h lib/TinyXML2/tinyxml2.h lib/TinyXML2/tinyxml2.cpp datastructures/dcel/graph/graph.cpp datastructures/dcel/graph/graph.h datastructures/dcel/graph/node.cpp datastructures/dcel/graph/node.h datastructures/dcel/graph/edge.cpp datastructures/dcel/graph/edge.h)
