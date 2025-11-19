cmake_minimum_required(VERSION 3.10)

project(作业,李林24123205,OOP,Week4,github@linull24)

set(CMAKE_CXX_STANDARD 23)

add_library(myString STATIC myString.cpp myStringBinData.cpp myStringInterface.cpp myStringProxy.cpp )

add_executable(tester tester.cpp)
target_link_libraries(tester myString)
