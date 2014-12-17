CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(versor_cmake)

SET(CMAKE_CXX_FLAGS "-std=c++11")

INCLUDE_DIRECTORIES(
  /home/lars/lib/versor/vsr/
  /home/lars/lib/versor/ext/gfx/
  /home/lars/lib/versor/ext/glv/
  /home/lars/lib/versor/ext/
)

LINK_DIRECTORIES(
  /home/lars/lib/versor/build/lib/
  /home/lars/lib/versor/ext/glv/build/lib/
)

ADD_EXECUTABLE(rotations rotations.cpp)

ADD_EXECUTABLE(xBasic xBasic.cpp)

TARGET_LINK_LIBRARIES(rotations vsr GLV)
TARGET_LINK_LIBRARIES(xBasic vsr GLV GLEW GLU GL glut)



