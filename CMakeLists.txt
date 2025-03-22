cmake_minimum_required(VERSION 3.30)
project(rpg_generator)

set(CMAKE_CXX_STANDARD 20)

add_executable(rpg_generator main.cpp
        Character.cpp
        Character.h
        item.cpp
        item.h
        types.h)
