cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project("translator")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(sym_table src/SymbolTable.cpp)
target_include_directories(sym_table PRIVATE include)
target_compile_definitions(sym_table PRIVATE cxx_std_17)

add_library(errors src/Errors.cpp)
target_include_directories(errors PRIVATE include)
target_compile_definitions(errors PRIVATE cxx_std_17)

add_library(scanner src/Scanner.cpp)
target_include_directories(scanner PRIVATE include)
target_link_libraries(scanner PRIVATE errors)
target_compile_definitions(scanner PRIVATE cxx_std_17)

add_library(parser src/Parser.cpp)
target_include_directories(parser PRIVATE include)
target_link_libraries(parser PRIVATE errors)
target_compile_definitions(parser PRIVATE cxx_std_17)

add_executable(translator ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_include_directories(translator PRIVATE include)
target_link_libraries(translator sym_table scanner parser)
target_compile_definitions(translator PRIVATE cxx_std_17)



target_compile_options(scanner PUBLIC -g)

