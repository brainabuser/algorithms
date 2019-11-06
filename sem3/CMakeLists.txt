cmake_minimum_required(VERSION 3.14)
project(sem3)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem3 N.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")