include(ExternalProject)
ExternalProject_Add(gfx
  SOURCE_DIR ../ext/gfx
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND "")
ExternalProject_Get_Property(gfx SOURCE_DIR)
set(GFX_INCLUDE_DIRS ${SOURCE_DIR} ${SOURCE_DIR}/gfx)
message(${GFX_INCLUDE_DIRS})
