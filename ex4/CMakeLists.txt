cmake_minimum_required(VERSION 3.25)
project(ex4)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex4 main.cpp Dense.cpp Dense.h Matrix.cpp Matrix.h Activation.cpp Activation.h MlpNetwork.cpp MlpNetwork.h)
