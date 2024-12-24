cmake_minimum_required(VERSION 3.25)
project(ex3a C)

set(CMAKE_C_STANDARD 11)

add_executable(ex3a tweets_generator.c markov_chain.h markov_chain.c linked_list.c linked_list.h)
