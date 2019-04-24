cmake_minimum_required(VERSION 3.13)
project(Geometry_Contest)

set(CMAKE_CXX_STANDARD 14)

add_executable(Geometry_Contest delaunator.hpp main.cpp io/reader.cpp io/reader.h simpleChecker.cpp simpleChecker.h datastructures/vec.cpp datastructures/vec.h datastructures/line.cpp datastructures/line.h datastructures/polygon.cpp datastructures/polygon.h datastructures/quadtree.h datastructures/quadtree.cpp datastructures/lineseg.cpp datastructures/lineseg.h io/visualiser.cpp io/visualiser.h lib/TinyXML2/tinyxml2.h lib/TinyXML2/tinyxml2.cpp)
