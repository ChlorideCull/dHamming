cmake_minimum_required(VERSION 3.7)
project(hammdist)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -march=native")

set(SOURCE_FILES hammdist.c hammdist.h)
add_library(hammdist SHARED ${SOURCE_FILES})
