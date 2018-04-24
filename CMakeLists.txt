cmake_minimum_required(VERSION 2.8)
project(ram_wong_clustering)

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_BUILD_TYPE Debug)

#add_definitions(-DTEST)

add_executable(ram_wong_clustering main.cpp parse.cpp node.cpp)
