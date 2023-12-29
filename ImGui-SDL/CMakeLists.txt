# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project(vocabulary_imgui_sdl C CXX)

macro(setup_module)
	# Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")

	# Core dependency
	add_dependency_module(${CMAKE_CURRENT_SOURCE_DIR}/../core vocabulary_core)
	module_message("vocabulary_core_INCLUDES: ${vocabulary_core_INCLUDES}")

	# abstract_ui_imgui dependency
	add_dependency_module(${DEPS}/abstract_ui/sdl_imgui abstract_ui_sdl_imgui)

	# android special source dependencies
	if (DEFINED ANDROID)
		set(ANDROID_PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/android-project)
		set(ANDROID_PROJ_DIR ${ANDROID_PROJ_ROOT}/app/jni)
		add_subdirectory(${ANDROID_PROJ_DIR}/jni_bridge)
		module_add_includes(${JNI_BRIDGE_DIR}/include)
	endif()

	# Assign all the headers to ${HEADERS} variable and use it in add_src() macro
	set_headers()
	add_src(
		${HEADERS} # for IDE
		main_sdl_imgui.cpp
		# main_imgui_test.cpp
		# uncomment if want to use lua scenario instead of SDL
		# main_lua.cpp
	)

	# make available includes like core/include/something
	module_add_includes(${CMAKE_CURRENT_SOURCE_DIR}/..)

	# Add library or executable
	module_add_library_or_executable()

	# android jni library linkage
	# TODO: move to abstract_ui_sdl_imgui
	if (DEFINED ANDROID)
		target_link_libraries(${MODULE_NAME} PRIVATE jni_bridge)
	endif()

	if (WIN32)
		add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${MODULE_NAME}> $<TARGET_FILE_DIR:${MODULE_NAME}>
			COMMAND_EXPAND_LISTS
		)
	endif()
	# set_target_properties(${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endmacro()

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
