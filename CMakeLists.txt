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

set(VSR_INCLUDE_DIRS include include/vsr)

include_directories(${VSR_INCLUDE_DIRS})

set(VSR_LIBRARY vsr)
file(GLOB VSR_SRCS src/space/*.cpp)

if(BUILD_GRAPHICS)
  message("-- Build with graphics")

  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(GLUT REQUIRED)

  # Build external libraries
  include(external_glv)
  include(external_gfx)
  include(external_gl2ps)

  set(VSR_INCLUDE_DIRS 
    ${VSR_INCLUDE_DIRS} 
    ${GLV_INCLUDE_DIR}
    ${GFX_INCLUDE_DIRS}
    ${GL2PS_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR})

  include_directories(${VSR_INCLUDE_DIRS})

  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GL2PS_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLV_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLUT_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${OPENGL_LIBRARY})
  list(APPEND VSR_LIBRARY_DEPENDENCIES ${GLEW_LIBRARY})

  file(GLOB VSR_GL_SRCS src/draw/GL/*.cpp)
  file(GLOB VSR_GLES_SRCS src/draw/GLES/*.cpp)

  add_library(${VSR_LIBRARY} ${VSR_SRCS} ${VSR_GL_SRCS} ${VSR_GLES_SRCS})
  target_link_libraries(${VSR_LIBRARY} ${VSR_LIBRARY_DEPENDENCIES})
  add_dependencies(${VSR_LIBRARY} ${GL2PS_LIBRARY} ${GLV_LIBRARY})

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

file(GLOB VSR_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/*.h)
install(FILES ${VSR_HDRS} DESTINATION include/vsr)
file(GLOB VSR_DETAIL_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/detail/*.h)
install(FILES ${VSR_DETAIL_HDRS} DESTINATION include/vsr/detail)
file(GLOB VSR_DRAW_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/draw/*.h)
install(FILES ${VSR_DRAW_HDRS} DESTINATION include/vsr/draw)
file(GLOB VSR_FORM_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/form/*.h)
install(FILES ${VSR_FORM_HDRS} DESTINATION include/vsr/form)
file(GLOB VSR_SPACE_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/space/*.h)
install(FILES ${VSR_SPACE_HDRS} DESTINATION include/vsr/space)
file(GLOB VSR_UTIL_HDRS ${CMAKE_SOURCE_DIR}/include/vsr/util/*.h)
install(FILES ${VSR_UTIL_HDRS} DESTINATION include/vsr/util)

file(GLOB GFX_HDRS ${CMAKE_SOURCE_DIR}/ext/gfx/gfx/*.h)
install(FILES ${GFX_HDRS} DESTINATION include/gfx/)
file(GLOB GFX_UTIL_HDRS ${CMAKE_SOURCE_DIR}/ext/gfx/gfx/util/*.h
  ${CMAKE_SOURCE_DIR}/ext/gfx/gfx/util/*.hpp)
install(FILES ${GFX_UTIL_HDRS} DESTINATION include/gfx/util)

file(GLOB GLV_HDRS ${CMAKE_SOURCE_DIR}/ext/glv/GLV/*.h)
install(FILES ${GLV_HDRS} DESTINATION include/GLV/)

file(GLOB GL2PS_HDRS ${CMAKE_SOURCE_DIR}/ext/gl2ps/*.h)
install(FILES ${GL2PS_HDRS} DESTINATION include/gl2ps/)

install(TARGETS ${VSR_LIBRARY}
  EXPORT VersorTargets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX})

#install(FILES ${PROJECT_BINARY_DIR}/libGLV.a 
  #DESTINATION lib${LIB_SUFFIX})

#install(TARGETS ${GLV_LIBRARY}
  #EXPORT VersorTargets
  #RUNTIME DESTINATION bin
  #LIBRARY DESTINATION lib${LIB_SUFFIX}
  #ARCHIVE DESTINATION lib${LIB_SUFFIX})

#install(TARGETS ${GL2PS_LIBRARY}
  #EXPORT VersorTargets
  #RUNTIME DESTINATION bin
  #LIBRARY DESTINATION lib${LIB_SUFFIX}
  #ARCHIVE DESTINATION lib${LIB_SUFFIX})

export(TARGETS ${VSR_LIBRARY} FILE "${PROJECT_BINARY_DIR}/VersorTargets.cmake")
export(PACKAGE ${VSR_LIBRARY})
configure_file(cmake/VersorConfig.cmake.in
    ${PROJECT_BINARY_DIR}/VersorConfig.cmake @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/VersorConfig.cmake DESTINATION share/versor)

install(EXPORT VersorTargets DESTINATION share/versor)
install(FILES package.xml DESTINATION share/versor)
