macro(set_build_directory)
  # Build directory name
  if(CMAKE_CXX_COMPILER EQUAL "g++")
    set(BUILD_DIR_NAME "Build-g++")
  else()
    set(BUILD_DIR_NAME "Build-cmake")
  endif()
endmacro(set_build_directory)
