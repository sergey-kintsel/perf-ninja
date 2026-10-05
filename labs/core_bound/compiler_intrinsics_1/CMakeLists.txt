cmake_minimum_required(VERSION 3.25)

project(lab)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize")

string(REGEX MATCH "^(.*)[\\/]labs[\\/].*$" repo "${CMAKE_CURRENT_SOURCE_DIR}")
include(${CMAKE_MATCH_1}/tools/labs.cmake)
