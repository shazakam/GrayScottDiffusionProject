cmake_minimum_required(VERSION 3.10)
project(GrayScottDiffusionProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)

include_directories(include ${MPI_INCLUDE_PATH})

add_executable(grayscott src/main.cpp)

target_link_libraries(grayscott ${MPI_LIBRARIES})

