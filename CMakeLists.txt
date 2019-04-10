cmake_minimum_required(VERSION 3.13)
project(Geometry_Contest)

set(CMAKE_CXX_STANDARD 14)

add_executable(Geometry_Contest delaunator.hpp main.cpp io/reader.cpp io/reader.h simpleChecker.cpp simpleChecker.h datastructures/vec.cpp datastructures/vec.h datastructures/line.cpp datastructures/line.h datastructures/polygon.cpp datastructures/polygon.h)
