cmake_minimum_required(VERSION 2.6)

project(Versor)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(VSR_VERSION_MAJOR 3)
set(VSR_VERSION_MINOR 0)
set(VSR_VERSION_PATCH 0)
set(VSR_VERSION
    ${VSR_VERSION_MAJOR}.${VSR_VERSION_MINOR}.${VSR_VERSION_PATCH})
message("-- Building Versor ${VSR_VERSION_MAJOR}.${VSR_VERSION_MINOR}.${VSR_VERSION_PATCH}")

option(BUILD_RASPBERRY "Build for Raspberry PI" OFF)
option(BUILD_GRAPHICS "Build graphics" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTING "Enable tests" OFF)
option(BUILD_DOCUMENTATION "Build User's Guide (html)" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -U__STRICT_ANSI__")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth-1200")
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -Wno-switch -Wno-deprecated-declarations -Wno-int-to-pointer-cast")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U__STRICT_ANSI__")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-switch -Wno-int-to-pointer-cast") 

include_directories(
  include
  include/vsr/)

set(VSR_LIBRARY vsr)
file(GLOB VSR_SRCS src/space/*.cpp)

if(BUILD_GRAPHICS)
  message("-- Build with graphics")

  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(GLUT REQUIRED)

  find_package(GLV REQUIRED)
  find_package(gfx REQUIRED)

  include_directories(
    ${GLV_INCLUDE_DIR}
    ${GFX_INCLUDE_DIR}
    ${GFX_INCLUDE_DIR}/gfx
    ${GLEW_INCLUDE_DIR}
    )

  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLV_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLUT_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${OPENGL_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLEW_LIBRARY})

  file(GLOB VSR_GL_SRCS src/draw/GL/*.cpp)
  file(GLOB VSR_GLES_SRCS src/draw/GLES/*.cpp)
  file(GLOB GL2PS_SRC ${GL2PS_DIR}/gl2ps.c)
  
  #set(GL2PS_SRC ${GL2PS_DIR}/gl2ps.c)

  add_library(${VSR_LIBRARY} ${VSR_SRCS} ${VSR_GL_SRCS} ${VSR_GLES_SRCS} ${GL2PS_SRC})
  target_link_libraries(${VSR_LIBRARY} ${VSR_LIBRARY_DEPENDENCIES})

else(BUILD_GRAPHICS)
  message("-- Do not build with graphics")
  add_library(${VSR_LIBRARY} ${VSR_SRCS})
endif(BUILD_GRAPHICS)

if (BUILD_EXAMPLES)
  message("-- Build the examples")
  add_subdirectory(examples)
else (BUILD_EXAMPLES)
  message("-- Do not build any example")
endif (BUILD_EXAMPLES)

if(BUILD_TESTING)
  message("-- Build the tests.")
else(BUILD_TESTING)
  message("-- Do not build any tests")
endif(BUILD_TESTING)

if(BUILD_DOCUMENTATION)
  message("-- Build the HTML documentation")
else(BUILD_DOCUMENTATION)
  message("-- Do not build the HTML documentation")
endif(BUILD_DOCUMENTATION)

install(FILES package.xml DESTINATION share/versor)
