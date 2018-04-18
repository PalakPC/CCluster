cmake_minimum_required(VERSION 3.5)
project(ram_wong_clustering)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_definitions(-DTEST)

add_executable(ram_wong_clustering main.cpp parse.cpp node.cpp)
