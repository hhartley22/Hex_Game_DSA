cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_FOLDER ./include)
include_directories(${INCLUDE_FOLDER})

add_subdirectory(src)