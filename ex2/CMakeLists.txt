cmake_minimum_required(VERSION 3.25)
project(ex2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ex2 main.c sort_bus_lines.c sort_bus_lines.h test_bus_lines.c test_bus_lines.h)
