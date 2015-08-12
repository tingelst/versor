include(ExternalProject)
find_package(Git REQUIRED)
ExternalProject_Add(gfx
  PREFIX ${CMAKE_BINARY_DIR}/gfx
  GIT_REPOSITORY https://github.com/tingelst/gfx.git 
  GIT_TAG devel
  TIMEOUT 10
  UPDATE_COMMAND ${GIT_EXECUTABLE} pull
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND "")

ExternalProject_Get_Property(gfx SOURCE_DIR)
set(GFX_INCLUDE_DIR ${SOURCE_DIR})
set(GL2PS_DIR ${SOURCE_DIR}/gl2ps)
