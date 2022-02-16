cmake_minimum_required(VERSION 3.21)
project(Turing_Complete C)

set(CMAKE_C_STANDARD 11)

include_directories(Compiler)

set(SOURCE_FILES Compiler/main.c Compiler/util.h Compiler/util.c)

add_executable(Turing_Complete ${SOURCE_FILES})
