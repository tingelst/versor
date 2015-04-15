cmake_minimum_required(VERSION 3.1)
project(versor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -ftemplate-depth-5000  -Wno-switch -Wno-int-to-pointer-cast")

include_directories(vsr)

add_library(vsr src/vsr_cga3D_op.cpp)

add_executable(rotations test/rotations.cpp)
target_link_libraries(rotations vsr)