#CMAKE FOR The Versor Geometric Algebra Mathematics Library 

#VERSION
cmake_minimum_required(VERSION 2.8)

#POLICIES
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
endif(COMMAND cmake_policy)

#PROJECT
project(VERSOR)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -U__STRICT_ANSI__ -O3 -ftemplate-depth-1200 -Wno-switch -Wno-deprecated-declarations -Wno-int-to-pointer-cast")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U__STRICT_ANSI__ -nostdinc++ -O3 -ftemplate-depth-1200 -Wno-switch -Wno-int-to-pointer-cast") 

#PROJECT INCLUDE AND LINK
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/vsr/)

file(GLOB core src/space/*.cpp)

add_library(vsr ${core})
link_directories(${PROJECT_BINARY_DIR})


set(vsr_libraries vsr)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

if(${BUILD_GRAPHICS})
  
  #OPTIONAL ADD GFX AS SUBDIRECTORY TO BUILD GRAPHICS DEMOS
  add_subdirectory(ext/gfx)

  #GET INCLUDE DIRECTORIES, LINK DIRECTORIES, AND LINKED LIBS
  get_property(GFX_LIBRARIES GLOBAL PROPERTY GFX_LIBRARIES)
  get_property(GFX_INCLUDE_DIR GLOBAL PROPERTY GFX_INCLUDE_DIR)
  get_property(GFX_LINK_DIR GLOBAL PROPERTY GFX_LINK_DIR)

  include_directories(${GFX_INCLUDE_DIR})
  link_directories(${GFX_LINK_DIR})

  file(GLOB graphicsGL src/draw/GL/*.cpp)
  file(GLOB graphicsGLES src/draw/GLES/*.cpp)

  if(${RASPBERRY})
    add_library(vsrGfx ${graphicsGLES}) 
  else()
    add_library(vsrGfx ${graphicsGL} ${graphicsGLES}) 
  endif()

  set(vsr_libraries  ${vsr_libraries} vsrGfx)
  set(libraries ${vsr_libraries} ${GFX_LIBRARIES}  ) 

  file(GLOB examples examples/*.cpp)
  foreach(filename ${examples})
    get_filename_component(target ${filename} NAME_WE)
    add_executable(${target} ${filename} )
    target_link_libraries(${target} ${libraries})
  endforeach()

endif()

if(${RUN_TESTS})
  find_package(Catch REQUIRED)
  include_directories(${CATCH_INCLUDE_DIR})
  enable_testing(true)
  #CORE TEST TARGETS
  file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)
  foreach(filename ${tests})
    get_filename_component(target ${filename} NAME_WE)
    add_executable(${target} ${filename} )
    target_link_libraries(${target} vsr )
    #Finally add it to test execution -
    add_test(NAME ${target}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/${target} )
  endforeach()
endif()

#PRINT DIRECTORIES
get_property(link_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY LINK_DIRECTORIES)
message("VERSOR LINK DIRECTORES")
foreach(d ${link_dirs})
  message(STATUS "link dir='${d}'")
endforeach()
get_property(inc_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
message("VERSOR INCLUDE DIRECTORES")
foreach(d ${inc_dirs})
  message(STATUS "include dir='${d}'")
endforeach()

set_property(GLOBAL PROPERTY VSR_LIBRARIES ${vsr_libraries})
set_property(GLOBAL PROPERTY VSR_INCLUDE_DIR "${inc_dirs}")
set_property(GLOBAL PROPERTY VSR_LINK_DIR "${link_dirs}")
