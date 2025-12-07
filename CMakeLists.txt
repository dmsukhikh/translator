cmake_minimum_required(VERSION 3.10)
project("translator")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sym_table src/SymbolTable.cpp)
target_include_directories(sym_table PRIVATE include)

add_executable(translator ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(translator sym_table)

