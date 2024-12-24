cmake_minimum_required(VERSION 3.25)
project(ex5)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex5 Movie.cpp Movie.h print_main.cpp User.cpp User.h UsersLoader.cpp UsersLoader.h
        RecommendationSystem.cpp RecommendationSystem.h RecommendationSystemLoader.cpp RecommendationSystemLoader.h)
