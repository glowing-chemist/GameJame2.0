cmake_minimum_required (VERSION 3.10)
project (WALL)


set(CMAKE_CXX_STANDARD 17)

add_subdirectory("../Bell" ${CMAKE_CURRENT_BINARY_DIR}/Bell)

add_executable("Wall" main.cpp)