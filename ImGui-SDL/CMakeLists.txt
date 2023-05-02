# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project(vocabulary_imgui_sdl C CXX)

macro(setup_module)
	# Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")

	# option(LOG_ON "Turn on logging" ON)
	# Core dependency
	add_dependency_module(${CMAKE_SOURCE_DIR}/../core vocabulary_core)
	module_message("vocabulary_core_INCLUDES: ${vocabulary_core_INCLUDES}")
	module_add_includes(${vocabulary_core_INCLUDES})

	# android special source dependencies
	if (DEFINED ANDROID)
		set(ANDROID_PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/android-project)
		set(ANDROID_PROJ_DIR ${ANDROID_PROJ_ROOT}/app/jni)
		add_subdirectory(${ANDROID_PROJ_DIR}/jni_bridge)
		module_add_includes(${JNI_BRIDGE_DIR}/include)
	endif()

	# SDL dependency
	set(SDL_DIR ${DEPS}/SDL)
	set(SDL_BUILD_DIR ${SDL_DIR}/build)
	add_subdirectory(${SDL_DIR} ${SDL_BUILD_DIR} EXCLUDE_FROM_ALL)
	set(SDL_INCLUDES ${SDL_DIR}/include)

	# ImGui dependency
	set(IMGUI_DIR "${DEPS}/imgui")
	module_message("IMGUI_DIR: ${IMGUI_DIR}")
	# set(GLFW_DIR "${IMGUI_DIR}/libs/glfw-3.3.8.bin.WIN64")
	# set(GLFW_LIB_DIR "${IMGUI_DIR}/libs/glfw-3.3.8.bin.WIN64/lib-vc2022")

	add_library(imgui STATIC
		${IMGUI_DIR}/imgui.cpp
		${IMGUI_DIR}/imgui_draw.cpp
		${IMGUI_DIR}/imgui_widgets.cpp
		${IMGUI_DIR}/imgui_tables.cpp
		${IMGUI_DIR}/imgui_demo.cpp
		${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
		${IMGUI_DIR}/backends/imgui_impl_sdlrenderer.cpp
	)

	set(IMGUI_INCLUDES
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
		${GLFW_DIR}/include
		${SDL_INCLUDES}
	)
	target_include_directories(imgui PUBLIC ${IMGUI_INCLUDES})

	# Assign all the headers to ${HEADERS} variable and use it in add_src() macro
	set_headers()
	add_src(
		${HEADERS} # for IDE
		${UTILS_DIR}/src/ui/imgui/node.cpp
		${UTILS_DIR}/src/ui/imgui/app.cpp
		${UTILS_DIR}/src/ui/imgui/sdl_app.cpp
		${UTILS_DIR}/src/ui/imgui/widget.cpp
		${UTILS_DIR}/src/ui/imgui/window.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/text_input.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/text.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/label.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/button.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/dialog.cpp
		${UTILS_DIR}/src/ui/imgui/widget_factory.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_with_buttons.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_yes_no.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_message.cpp
		${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_input_text.cpp
		main_sdl_imgui.cpp
		# main_imgui_test.cpp
		# uncomment if want to use lua scenario instead of SDL
		# main_lua.cpp
	)

	# make available includes like core/include/something
	module_add_includes(${CMAKE_CURRENT_SOURCE_DIR}/..)

	# Add library or executable
	module_add_library_or_executable()

	# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications  
	message("TARGETS: ${BUILDSYSTEM_TARGETS}")
	if(TARGET SDL2::SDL2main)
		# It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
		target_link_libraries(${MODULE_NAME} PRIVATE SDL2::SDL2main)
	elseif(TARGET SDL2main)
		target_link_libraries(${MODULE_NAME} PRIVATE SDL2main)
	else()
		message( SEND_ERROR "No SDL2main target found!")
	endif()
	# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
	target_link_libraries(${MODULE_NAME} PRIVATE SDL2)

	target_link_libraries(${MODULE_NAME} PRIVATE imgui)

	# android jni library linkage
	if (DEFINED ANDROID)
		target_link_libraries(${MODULE_NAME} PRIVATE jni_bridge)
	endif()

	set_target_properties(${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endmacro()

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
