MACRO(GROUP_SRC SRCS PATH_RELATIVE_TO)
  foreach(FILE ${SRCS})
    # message("FILE: ${FILE}")
    #convert source file to absolute
    get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
    # Get the directory of the absolute source file
    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
    # Remove common directory prefix to make the group
    # message("PATH_RELATIVE_TO: ${PATH_RELATIVE_TO}, GROUP: ${GROUP}, FILE: ${FILE}, ABSOLUTE_PATH: ${ABSOLUTE_PATH}, PARENT_DIR: ${PARENT_DIR}, PARENT_DIR: ${PARENT_DIR}")
    string(REPLACE "${PATH_RELATIVE_TO}" "" GROUP "${PARENT_DIR}")
    # message("GROUP after replace: ${GROUP}")
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    # Group into "Source Files" and "Header Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
      set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
      set(GROUP "Header Files${GROUP}")
    endif()
    # message("Put file ${FILE} in group ${GROUP}")
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
ENDMACRO(GROUP_SRC)
