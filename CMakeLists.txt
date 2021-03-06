cmake_minimum_required(VERSION 3.8)
project(dHamming)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# set(CMAKE_CXX_COMPILER /usr/bin/clang)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4 -fPIC")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(SOURCE_FILES_hammdist hammdist.c hammdist.h)
add_library(hammdist STATIC ${SOURCE_FILES_hammdist})

set(SOURCE_FILES_DHAMMING_HEADERS dHamming.hpp CompatMode.hpp Utils.hpp)
set(SOURCE_FILES_DHAMMING dHamming.cpp CompatMode.cpp Utils.cpp)
add_library(dHamming SHARED ${SOURCE_FILES_DHAMMING} ${SOURCE_FILES_DHAMMING_HEADERS})
target_link_libraries(dHamming PRIVATE hammdist)

set(SOURCE_FILES_EXEC main.cpp)
add_executable(Main ${SOURCE_FILES_EXEC})
target_link_libraries(Main PRIVATE dHamming)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
set_property(SOURCE dHamming.i PROPERTY CPLUSPLUS ON)
swig_add_library(dHammingPy LANGUAGE python SOURCES dHamming.i)
swig_link_libraries(dHammingPy ${PYTHON_LIBRARIES} dHamming)
