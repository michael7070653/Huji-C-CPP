cmake_minimum_required(VERSION 3.25)
project(ex1 C)

set(CMAKE_C_STANDARD 11)

add_executable(ex1 main.c tests.h tests.c cipher.c cipher.h)
