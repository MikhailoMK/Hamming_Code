cmake_minimum_required(VERSION 3.10)

project(Hamming_Code)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(Hamming hamming.cpp)

add_executable(hamming main.cpp)

target_link_libraries(hamming PRIVATE Hamming)
