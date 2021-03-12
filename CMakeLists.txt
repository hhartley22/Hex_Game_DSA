cmake_minimum_required(VERSION 3.17)
project(Assignment1)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_FOLDER ./include)
set(SRC_FOLDER ./src)
set(SRC_CODE src/Main.cpp)

include_directories(${INCLUDE_FOLDER} ${SRC_FOLDER})
add_executable(Assignment1 ${SRC_CODE})