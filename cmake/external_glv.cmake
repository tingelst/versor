include(ExternalProject)
#ExternalProject_Add(glv_library
  #PREFIX ${CMAKE_BINARY_DIR}/glv_library
  #SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/glv
  #CONFIGURE_COMMAND ""
  #BUILD_IN_SOURCE 1
  #BUILD_COMMAND ${CMAKE_MAKE_PROGRAM}
  #INSTALL_COMMAND ""
  #INSTALL_COMMAND cp ${CMAKE_SOURCE_DIR}/ext/glv/build/lib/libGLV.a ${CMAKE_BINARY_DIR}
  #)
#ExternalProject_Get_Property(glv_library SOURCE_DIR)
#set(GLV_INCLUDE_DIR ${SOURCE_DIR})
#ExternalProject_Get_Property(glv_library BINARY_DIR)
#set(GLV_LIBRARY_PATH ${BINARY_DIR}/build/lib/${CMAKE_FIND_LIBRARY_PREFIXES}GLV.a)
#set(GLV_LIBRARY GLV)
#add_library(${GLV_LIBRARY} STATIC IMPORTED GLOBAL)
#set_property(TARGET ${GLV_LIBRARY} PROPERTY IMPORTED_LOCATION ${GLV_LIBRARY_PATH})
#add_dependencies(${GLV_LIBRARY} glv_library)


find_package(Git REQUIRED)
include(ExternalProject)
ExternalProject_Add(glv_library
  PREFIX ${CMAKE_BINARY_DIR}/glv_library
  GIT_REPOSITORY https://github.com/tingelst/GLV.git
  GIT_TAG cmake
  TIMEOUT 10
  UPDATE_COMMAND ""
  CMAKE_ARGS -DNO_EXAMPLES=ON
  #INSTALL_COMMAND cp ${CMAKE_SOURCE_DIR}/ext/glv/build/lib/libGLV.a ${CMAKE_BINARY_DIR}
  #INSTALL_COMMAND ""
  )
ExternalProject_Get_Property(glv_library SOURCE_DIR)
set(GLV_INCLUDE_DIR ${SOURCE_DIR})
ExternalProject_Get_Property(glv_library BINARY_DIR)
set(GLV_LIBRARY_PATH ${CMAKE_BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}GLV.a)
set(GLV_LIBRARY GLV)
add_library(${GLV_LIBRARY} STATIC IMPORTED GLOBAL)
set_property(TARGET ${GLV_LIBRARY} PROPERTY IMPORTED_LOCATION ${GLV_LIBRARY_PATH})
install(TARGETS ${GLV_LIBRARY}
  EXPORT VersorTargets
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  )

add_dependencies(${GLV_LIBRARY} glv_library)
