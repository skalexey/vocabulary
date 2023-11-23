macro(setup_deps)
	# set deps variables
	set(${MODULE_NAME}_deps "$ENV{${MODULE_NAME}_deps}")
	set(${MODULE_NAME}_deps "${${MODULE_NAME}_deps}" PARENT_SCOPE)

	if("${DEPS}" STREQUAL "")
		set(DEPS ${${MODULE_NAME}_deps})
	endif()

	if("${DEPS}" STREQUAL "")
		file(TO_CMAKE_PATH "$ENV{build_deps}" DEPS)
		module_message("Try to set DEPS to build_deps. Read value: '${DEPS}'")
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
	if("${ARGV2}" STREQUAL "LINK_ONLY")
		# target_link_directories(${MODULE_NAME} PRIVATE ${dir})
	elseif("${ARGV2}" STREQUAL "INCLUDE_ONLY")
		# add_subdirectory(${dir} ${dir}/${BUILD_DIR_NAME} EXCLUDE_FROM_ALL)
	elseif("${ARGV2}" STREQUAL "EXECUTE_SEPARATELY")
		execute_process(
			COMMAND ${CMAKE_COMMAND} -S ${dir} -B ${dir}/${BUILD_DIR_NAME}
		)
		# No properties (e.g., ${name}_INCLUDES) will be available here
	else()
		include(FetchContent)
		FetchContent_Declare(
			${name}
			SOURCE_DIR ${dir}
		)
		FetchContent_GetProperties(${name})
		if(NOT ${name}_POPULATED)
			module_message("FetchContent_Populate(${name})")
			FetchContent_Populate(${name})
			add_subdirectory(${${name}_SOURCE_DIR} ${${name}_BINARY_DIR})
		else()
			get_directory_property(${name}_INCLUDES DIRECTORY ${${name}_SOURCE_DIR} DEFINITION ${name}_INCLUDES)
		endif()
	endif()
	if ("${${name}_INCLUDES}" STREQUAL "")
		message(SEND_ERROR "${MODULE_NAME}: ERROR: ${name}_INCLUDES is not specified")
	endif()
	module_add_includes(${${name}_INCLUDES})
	set(DEPENDENCY_LIBRARIES ${DEPENDENCY_LIBRARIES} ${name})
	module_message("add_dependency_module: ${name} located in ${dir}")
	module_message("dependency includes: ${${name}_INCLUDES}")
endmacro(add_dependency_module)

macro(add_dependency_library name)
	set(DEPENDENCY_LIBRARIES ${DEPENDENCY_LIBRARIES} ${name})
endmacro(add_dependency_library)