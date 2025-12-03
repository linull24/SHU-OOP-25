cmake_minimum_required(VERSION 3.10)
project(LinkedListWasm)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calc
    interface.cpp
)

set_target_properties(calc PROPERTIES
    SUFFIX ".js"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../../output"
)

target_link_options(calc PRIVATE
    "SHELL:-lembind"
    "SHELL:-s MODULARIZE=1"
    "SHELL:-s EXPORT_ES6=1"
    -O3
)
