include(ExternalProject)
find_package(Git REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
ExternalProject_Add(glv_library
  PREFIX ${CMAKE_BINARY_DIR}/glv_library
  GIT_REPOSITORY https://github.com/tingelst/GLV.git
  GIT_TAG cmake
  TIMEOUT 10
  UPDATE_COMMAND ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ${CMAKE_COMMAND} -DNO_EXAMPLES=ON ../glv_library
  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  INSTALL_COMMAND "")
ExternalProject_Get_Property(glv_library SOURCE_DIR)
set(GLV_INCLUDE_DIR ${SOURCE_DIR})
set(GLV_LIBRARY_PATH ${SOURCE_DIR}/build/lib/${CMAKE_FIND_LIBRARY_PREFIXES}GLV.a)
set(GLV_LIBRARY GLV)
add_library(${GLV_LIBRARY} STATIC IMPORTED GLOBAL)
set_property(TARGET ${GLV_LIBRARY} PROPERTY IMPORTED_LOCATION ${GLV_LIBRARY_PATH})
add_dependencies(${GLV_LIBRARY} glv_library)
