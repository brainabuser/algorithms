cmake_minimum_required(VERSION 3.14)
project(yandex_yellow_belt)

set(CMAKE_CXX_STANDARD 17)

add_executable(yandex_yellow_belt week_2/test_person.cpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")