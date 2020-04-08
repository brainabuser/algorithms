cmake_minimum_required(VERSION 3.14)
project(my_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_game main.cpp Character.cpp Character.h Game.cpp Game.h Archer.h Warrior.h Wizard.h Army.h Army.cpp)