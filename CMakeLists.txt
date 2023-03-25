# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project (vocabulary C CXX)

include(group.cmake)

if(MSVC)
	# fix __cplusplus macro for MSVC
	add_compile_options(
		"/Zc:__cplusplus"
		# "/std:c++latest"
	)
endif()
set(CMAKE_CXX_STANDARD 17)

if ("${MODULE_NAME}" STREQUAL "")
	message("MODULE_NAME is empty. Set to 'vocabulary'")
	set(MODULE_NAME vocabulary)
else()
	message("MODULE_NAME is set externally to '${MODULE_NAME}'")
endif()

option(INHERIT_PARENT_SRC "Adds all parent's source files" OFF)
option(INHERIT_PARENT_LIBS "Adds all parent's libraries" OFF)

message("${MODULE_NAME}: INHERIT_PARENT_SRC is ${INHERIT_PARENT_SRC}")
message("${MODULE_NAME}: INHERIT_PARENT_LIBS is ${INHERIT_PARENT_LIBS}")

if (LOG_ON)
	add_compile_definitions("LOG_ON")
	message("${MODULE_NAME}: LOG_ON is defined")
else()
	message("${MODULE_NAME}: LOG_ON is not defined")
endif ()
if (LOG_LEVEL_VERBOSE)
	add_compile_definitions("LOG_LEVEL_VERBOSE")
	message("${MODULE_NAME}: LOG_LEVEL_VERBOSE is defined")
else()
	message("${MODULE_NAME}: LOG_LEVEL_VERBOSE is not defined")
endif ()
if (LOG_LEVEL_DEBUG)
	add_compile_definitions("LOG_LEVEL_DEBUG")
	message("${MODULE_NAME}: LOG_LEVEL_DEBUG is defined")
else()
	message("${MODULE_NAME}: LOG_LEVEL_DEBUG is not defined")
endif()

# set deps variables
set(vocabulary_deps "$ENV{vocabulary_deps}")
set(vocabulary_deps "${vocabulary_deps}" PARENT_SCOPE)
if ("${DEPS}" STREQUAL "")
	set(DEPS ${vocabulary_deps})
endif()
if ("${DEPS}" STREQUAL "")
	file(TO_CMAKE_PATH "$ENV{build_deps}" DEPS)
endif()
if ("${DEPS}" STREQUAL "")
	message(SEND_ERROR "${MODULE_NAME}: ERROR: DEPS is not specified. Take the default value")
	set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
else()
	message("${MODULE_NAME}: DEPS: ${DEPS}")
endif()
set(DEPS ${DEPS} PARENT_SCOPE)

# Build directory name
if (CMAKE_CXX_COMPILER EQUAL "g++")
	set(BUILD_DIR_NAME "Build-g++")
else ()
	set(BUILD_DIR_NAME "Build-cmake")
endif ()

# Utils dependency
set(UTILS_DIR "${DEPS}/Utils")
file(GLOB_RECURSE UTILS_HEADERS "${UTILS_DIR}/include/*")
set(EXTERNAL_HEADERS ${EXTERNAL_HEADERS}
	${UTILS_HEADERS}
)
GROUP_SRC("${UTILS_HEADERS}" "${UTILS_DIR}/include")

# Set and add includes
if (NOT "${INCLUDES}" STREQUAL "")
	message("Add extra includes: ${INCLUDES}")
endif()

# DMBCore dependency
add_subdirectory(${DEPS}/DataModelBuilder/Core ${DEPS}/DataModelBuilder/Core/${BUILD_DIR_NAME})
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES}
	${DMBCORE_INCLUDES}
)

# Networking dependency
add_subdirectory(${DEPS}/Networking/http ${DEPS}/Networking/http/${BUILD_DIR_NAME})
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES}
	${http_INCLUDES}
)

# Lua dependency
set (LUA_DIR "${DEPS}/lua-5.4.4")
message("${MODULE_NAME}: LUA_DIR: ${LUA_DIR}")
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES}
	${LUA_DIR}/src
)

# SDL dependency
set(SDL_DIR ${DEPS}/SDL)
set(SDL_BUILD_DIR ${SDL_DIR}/build)
add_subdirectory(${SDL_DIR} ${SDL_BUILD_DIR} EXCLUDE_FROM_ALL)
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES} ${SDL_DIR}/include)

# Include ImGui
set(IMGUI_DIR "${DEPS}/imgui")
message("IMGUI_DIR: ${IMGUI_DIR}")
# set(GLFW_DIR "${IMGUI_DIR}/libs/glfw-3.3.8.bin.WIN64")
# set(GLFW_LIB_DIR "${IMGUI_DIR}/libs/glfw-3.3.8.bin.WIN64/lib-vc2022")

# Boost dependency
set (BOOST_DIR "${DEPS}/boost_1_81_0")
message("${MODULE_NAME}: BOOST_DIR: ${BOOST_DIR}")
set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES}
	${BOOST_DIR}
)

set(CUSTOM_INCLUDES ${CUSTOM_INCLUDES}
	${IMGUI_DIR}
	${IMGUI_DIR}/backends
	${GLFW_DIR}/include
)
add_library(imgui STATIC
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/imgui_tables.cpp
	${IMGUI_DIR}/imgui_demo.cpp
	${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
	${IMGUI_DIR}/backends/imgui_impl_sdlrenderer.cpp
)

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

# android special source dependencies
if (DEFINED ANDROID)
	set(ANDROID_PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/android-project)
	set(ANDROID_PROJ_DIR ${ANDROID_PROJ_ROOT}/app/jni)
	add_subdirectory(${ANDROID_PROJ_DIR}/jni_bridge)
endif()


# Set includes
set(${MODULE_NAME}_INCLUDES ${${MODULE_NAME}_INCLUDES} 
	${CUSTOM_INCLUDES}
	${INCLUDES}
	${JNI_BRIDGE_DIR}/include
	"include"
)

set(${MODULE_NAME}_INCLUDES ${${MODULE_NAME}_INCLUDES} PARENT_SCOPE)
message("${MODULE_NAME}_INCLUDES: ${${MODULE_NAME}_INCLUDES}")

if (NOT "${${MODULE_NAME}_INCLUDES}" STREQUAL "")
	include_directories(${${MODULE_NAME}_INCLUDES})
endif()

# Inherit parent sources logic
if (INHERIT_PARENT_SRC)
	set(SRC ${PARENT_SRC})
	message("'${MODULE_NAME}' project PARENT_SRC: ${PARENT_SRC}")
endif()
# End of Inherit parent sources logic

message("${MODULE_NAME}: UTILS_DIR: ${UTILS_DIR}")

# set headers
file(GLOB_RECURSE HEADERS ${HEADERS} "include/*")
message("'${MODULE_NAME}' project HEADERS: ${HEADERS}")
message("'${MODULE_NAME}' project SRC: ${SRC}")

# set sources
file(GLOB_RECURSE THIS_SRC CONFIGURE_DEPENDS "src/*")
set(SRC ${SRC}
	${THIS_SRC}
	${UTILS_DIR}/src/networking/uploader_with_auth.cpp
	${UTILS_DIR}/src/networking/downloader_with_auth.cpp
	${UTILS_DIR}/src/networking/downloader_with_version_control.cpp
	${UTILS_DIR}/src/ui/imgui/sdl_app.cpp
	${UTILS_DIR}/src/ui/imgui/widgets/text_input.cpp
	${UTILS_DIR}/src/ui/imgui/widgets/dialog.cpp
	${UTILS_DIR}/src/ui/imgui/widget_factory.cpp
	${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_yes_no.cpp
	${UTILS_DIR}/src/ui/imgui/widgets/dialogs/dialog_message.cpp
	${UTILS_DIR}/src/ui/helpers/user_input.cpp
	${UTILS_DIR}/src/string_utils.cpp
	${UTILS_DIR}/src/file_utils.cpp
	${UTILS_DIR}/src/io_utils.cpp
	${UTILS_DIR}/src/datetime.cpp
	${HEADERS} # for IDE
	main_sdl_imgui.cpp
	# main_imgui_test.cpp
	# uncomment if want to use lua scenario instead of SDL
	# main_lua.cpp
)

# Set parent sources for further optional inheritance
set(PARENT_SRC ${PARENT_SRC} ${SRC})
set(PARENT_SRC ${PARENT_SRC} PARENT_SCOPE)

# add executable
if(BUILD_LIBRARY)
	message("BUILD_LIBRARY")
	add_library (${MODULE_NAME} ${SRC})
elseif(BUILD_SHARED_LIBRARY)
	message("BUILD_SHARED_LIBRARY")
	add_library (${MODULE_NAME} SHARED ${SRC})
else()
	message("BUILD_EXECUTABLE")
	add_executable (${MODULE_NAME} ${SRC})
endif()

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

target_link_libraries(${MODULE_NAME} PRIVATE lualib imgui DMBCore http)

# setup all sources target just for visibility of all the files used in IDE
if (NOT "${EXTERNAL_HEADERS}" STREQUAL "")
	message("EXTERNAL_HEADERS: ${EXTERNAL_HEADERS}")
	message("Create a separate target for external headers called 'external_headers'")
	add_library(external_headers ${EXTERNAL_HEADERS})
endif()


# android jni library linkage
if (DEFINED ANDROID)
	target_link_libraries(${MODULE_NAME} PRIVATE jni_bridge)
endif()

set_target_properties(${MODULE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

configure_file(assets/random_words.lua ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

if (WIN32)
	add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${MODULE_NAME}> $<TARGET_FILE_DIR:${MODULE_NAME}>
		COMMAND_EXPAND_LISTS
	)
endif()