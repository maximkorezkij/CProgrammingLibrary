cmake_minimum_required(VERSION 3.13)
project(Project C)

set(CMAKE_C_STANDARD 99)

include_directories(./inc)
include_directories(./src)

add_executable(Project
        include/func.h include/main.h
        src/main.c src/func.c src/help.c src/menu.c )
