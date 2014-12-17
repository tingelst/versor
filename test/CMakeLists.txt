CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(versor_cmake)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -ftemplate-depth-5000")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

INCLUDE_DIRECTORIES(
  /Users/lars/lib/versor/vsr/
  /Users/lars/lib/versor/ext/gfx/
  /Users/lars/lib/versor/ext/glv/
  /Users/lars/lib/versor/ext/
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
)

LINK_DIRECTORIES(
  /Users/lars/lib/versor/build/lib/
  /Users/lars/lib/versor/ext/glv/build/lib/
)

ADD_EXECUTABLE(rotations rotations.cpp)
#ADD_EXECUTABLE(xBasic xBasic.cpp)
#ADD_EXECUTABLE(xRobotArm xRobotArm.cpp)
#ADD_EXECUTABLE(xChain xChain.cpp)
ADD_EXECUTABLE(fk forward_kinematics.cpp)

TARGET_LINK_LIBRARIES(rotations vsr GLV)
#TARGET_LINK_LIBRARIES(xRobotArm vsr GLV ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
#TARGET_LINK_LIBRARIES(xBasic vsr GLV ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
#TARGET_LINK_LIBRARIES(xChain vsr GLV ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
TARGET_LINK_LIBRARIES(fk vsr GLV ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})




