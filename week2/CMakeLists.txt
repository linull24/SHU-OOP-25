cmake_minimum_required(VERSION 3.10)

project(作业,李林24123205,OOP,Week2,github@linull24)

set(CMAKE_CXX_STANDARD 23)

add_library(quadraticEquation STATIC QuadraticEquation.cpp)
add_library(complexUtils STATIC complexUtils.cpp)

add_executable(testComplex testComplex.cpp)
target_link_libraries(testComplex complexUtils)

add_executable(testQuadraticEquation testQuadraticEquation.cpp)
target_link_libraries(testQuadraticEquation quadraticEquation)
