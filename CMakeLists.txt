cmake_minimum_required(VERSION 3.26)
project(Games_MM)

set(CMAKE_CXX_STANDARD 17)

add_executable(Games_MM main.cpp)

target_include_directories(Games_MM PRIVATE ${PROJECT_SOURCE_DIR})
