cmake_minimum_required(VERSION 3.10)
project("translator")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(translator ${CMAKE_SOURCE_DIR}/src/main.cpp)
