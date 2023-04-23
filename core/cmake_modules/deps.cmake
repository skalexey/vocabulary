macro(setup_deps)
	# set deps variables
	set(${MODULE_NAME}_deps "$ENV{${MODULE_NAME}_deps}")
	set(${MODULE_NAME}_deps "${${MODULE_NAME}_deps}" PARENT_SCOPE)

	if("${DEPS}" STREQUAL "")
		set(DEPS ${${MODULE_NAME}_deps})
	endif()

	if("${DEPS}" STREQUAL "")
		file(TO_CMAKE_PATH "$ENV{build_deps}" DEPS)
	endif()

	if("${DEPS}" STREQUAL "")
		message(SEND_ERROR "${MODULE_NAME}: ERROR: DEPS is not specified. Take the default value")
		set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
	else()
		message("${MODULE_NAME}: DEPS: ${DEPS}")
	endif()

	set(DEPS ${DEPS} PARENT_SCOPE)
endmacro(setup_deps)

macro(add_dependency_module dir name)
	add_subdirectory(${dir} ${dir}/${BUILD_DIR_NAME})
	module_add_includes(${${name}_INCLUDES})
	set(DEPENDENCY_LIBRARIES ${DEPENDENCY_LIBRARIES} ${name})
endmacro(add_dependency_module)

