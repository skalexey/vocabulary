# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project(vocabulary_core C CXX)

macro(setup_module)
	set(CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
	set(CORE_DIR ${CORE_DIR} PARENT_SCOPE)

	module_message("Setting up module: ${MODULE_NAME}")
	
	# Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")
	file(GLOB_RECURSE UTILS_HEADERS "${UTILS_DIR}/include/*")
	# set(EXTERNAL_HEADERS ${EXTERNAL_HEADERS}
	# 	${UTILS_HEADERS}
	# )
	GROUP_SRC("${UTILS_HEADERS}" "${UTILS_DIR}/include")
	module_message("UTILS_DIR: ${UTILS_DIR}")

	# abstract_ui dependency
	add_dependency_module(${DEPS}/abstract_ui abstract_ui)

	# DMBCore dependency
	add_dependency_module(${DEPS}/DataModelBuilder/Core DMBCore)

	# Networking dependency
	add_dependency_module(${DEPS}/Networking/http http)

	# Lua dependency
	set (LUA_DIR "${DEPS}/lua-5.4.4")
	message("${MODULE_NAME}: LUA_DIR: ${LUA_DIR}")
	module_add_includes(${LUA_DIR}/src)

	# Boost dependency
	set (BOOST_DIR "${DEPS}/boost_1_81_0")
	message("${MODULE_NAME}: BOOST_DIR: ${BOOST_DIR}")
	module_add_includes(${BOOST_DIR})

	file(GLOB LUA_SRC "${LUA_DIR}/src/*.c")
	add_library (lualib STATIC
		${LUA_DIR}/src/lapi.c
		${LUA_DIR}/src/lcode.c
		${LUA_DIR}/src/lctype.c
		${LUA_DIR}/src/ldebug.c
		${LUA_DIR}/src/ldo.c
		${LUA_DIR}/src/ldump.c
		${LUA_DIR}/src/lfunc.c
		${LUA_DIR}/src/lgc.c
		${LUA_DIR}/src/llex.c
		${LUA_DIR}/src/lmem.c
		${LUA_DIR}/src/lobject.c
		${LUA_DIR}/src/lopcodes.c
		${LUA_DIR}/src/lparser.c
		${LUA_DIR}/src/lstate.c
		${LUA_DIR}/src/lstring.c
		${LUA_DIR}/src/ltable.c
		${LUA_DIR}/src/ltm.c
		${LUA_DIR}/src/lundump.c
		${LUA_DIR}/src/lvm.c
		${LUA_DIR}/src/lzio.c
		${LUA_DIR}/src/lauxlib.c
		${LUA_DIR}/src/lbaselib.c
		${LUA_DIR}/src/lcorolib.c
		${LUA_DIR}/src/ldblib.c
		${LUA_DIR}/src/liolib.c
		${LUA_DIR}/src/lmathlib.c
		${LUA_DIR}/src/loslib.c
		${LUA_DIR}/src/lstrlib.c
		${LUA_DIR}/src/ltablib.c
		${LUA_DIR}/src/loadlib.c
		${LUA_DIR}/src/linit.c
		${LUA_DIR}/src/lutf8lib.c
	)
	message("${MODULE_NAME}: Lua src: '${LUA_SRC}'")

	# Assign all the headers to ${HEADERS} variable and use it in add_src() macro
	add_src(
		${UTILS_DIR}/src/networking/uploader_with_auth.cpp
		${UTILS_DIR}/src/networking/downloader_with_auth.cpp
		${UTILS_DIR}/src/networking/downloader_with_version_control.cpp
		${UTILS_DIR}/include/utils/networking/sync_resources.h
		${UTILS_DIR}/src/string_utils.cpp
		${UTILS_DIR}/src/file_utils.cpp
		${UTILS_DIR}/src/io_utils.cpp
		${UTILS_DIR}/src/datetime.cpp
		${UTILS_DIR}/src/envar.cpp
		# uncomment if want to use lua scenario
		# main_lua.cpp
	)

	# For IDE
	add_headers_to_sources()
	
	# add library
	module_add_library()


	# set_target_properties(${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

	# setup all sources target just for visibility of all the files used in IDE
	if (NOT "${EXTERNAL_HEADERS}" STREQUAL "")
		module_message("EXTERNAL_HEADERS: ${EXTERNAL_HEADERS}")
		module_message("Create a separate target for external headers called 'external_headers'")
		add_library(external_headers ${EXTERNAL_HEADERS})
	endif()
endmacro()

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()

# For calling from final (executable) projects
macro(core_copy_assets to)
	copy_directory(${CORE_DIR}/assets ${to})
	add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${CORE_DIR}/assets"
			${to}/assets
	)
	# Uncomment to copy to the executable directory
	# COMMAND ${CMAKE_COMMAND} -E copy_directory
	# 	"${CORE_DIR}/assets"
	# 	$<TARGET_FILE_DIR:${MODULE_NAME}>/assets
endmacro()
