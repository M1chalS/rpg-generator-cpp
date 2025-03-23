cmake_minimum_required(VERSION 3.30)
project(rpg_generator)

set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/items.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/characters.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

add_executable(rpg_generator main.cpp
        Character.cpp
        Character.h
        item.cpp
        item.h
        types.h)
