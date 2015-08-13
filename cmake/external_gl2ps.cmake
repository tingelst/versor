include(ExternalProject)
ExternalProject_Add(gl2ps_library
  PREFIX ${CMAKE_BINARY_DIR}/gl2ps_library
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/gl2ps
  CMAKE_ARGS -DENABLE_PNG=OFF -DENABLE_ZLIB=OFF
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
  )
ExternalProject_Get_Property(gl2ps_library SOURCE_DIR)
set(GL2PS_INCLUDE_DIR ${SOURCE_DIR})
ExternalProject_Get_Property(gl2ps_library BINARY_DIR)
set(GL2PS_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}gl2ps.a)
set(GL2PS_LIBRARY gl2ps)
add_library(${GL2PS_LIBRARY} STATIC IMPORTED GLOBAL)
set_property(TARGET ${GL2PS_LIBRARY} PROPERTY IMPORTED_LOCATION ${GL2PS_LIBRARY_PATH})
add_dependencies(${GL2PS_LIBRARY} gl2ps_library)
