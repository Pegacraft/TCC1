cmake_minimum_required(VERSION 3.21)
project(Turing_Complete C)

set(CMAKE_C_STANDARD 11)

include_directories(Compiler)

add_executable(Turing_Complete
        Compiler/main.c)
