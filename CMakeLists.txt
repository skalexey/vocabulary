# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (vocabulary C CXX)

if(MSVC)
	# fix __cplusplus macro for MSVC
	add_compile_options(
		"/Zc:__cplusplus"
		"/std:c++latest"
	)
else()
	set(CMAKE_CXX_STANDARD 20)
endif()

option(INHERIT_PARENT_SRC "Adds all parent's source files" OFF)
option(INHERIT_PARENT_LIBS "Adds all parent's libraries" OFF)

message("vocabulary: INHERIT_PARENT_SRC is ${INHERIT_PARENT_SRC}")
message("vocabulary: INHERIT_PARENT_LIBS is ${INHERIT_PARENT_LIBS}")

if (LOG_ON)
	add_compile_definitions("LOG_ON")
	message("vocabulary: LOG_ON is defined")
else()
	message("vocabulary: LOG_ON is not defined")
endif ()
if (LOG_LEVEL_VERBOSE)
	add_compile_definitions("LOG_LEVEL_VERBOSE")
	message("vocabulary: LOG_LEVEL_VERBOSE is defined")
else()
	message("vocabulary: LOG_LEVEL_VERBOSE is not defined")
endif ()
if (LOG_LEVEL_DEBUG)
	add_compile_definitions("LOG_LEVEL_DEBUG")
	message("vocabulary: LOG_LEVEL_DEBUG is defined")
else()
	message("vocabulary: LOG_LEVEL_DEBUG is not defined")
endif()

# set deps variables
set(vocabulary_deps "$ENV{vocabulary_deps}")
set(vocabulary_deps "${vocabulary_deps}" PARENT_SCOPE)
if ("${DEPS}" STREQUAL "")
	set(DEPS ${vocabulary_deps})
endif()
if ("${DEPS}" STREQUAL "")
	set(DEPS "$ENV{build_deps}")
endif()
if ("${DEPS}" STREQUAL "")
	message(SEND_ERROR "vocabulary: ERROR: DEPS is not specified. Take the default value")
	set(DEPS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
else()
	message("vocabulary: DEPS: ${DEPS}")
endif()
set(DEPS ${DEPS} PARENT_SCOPE)

# Set and add includes
if (NOT "${INCLUDES}" STREQUAL "")
	message("Add extra includes: ${INCLUDES}")
endif()

set (LUA_DIR "${DEPS}/lua-5.4.4")
message("vocabulary: LUA_DIR: ${LUA_DIR}")
set(CUSTOM_INCLUDES
	${LUA_DIR}/src
)

#file(GLOB LUA_SRC "${LUA_DIR}/src/*.c")
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
# message("vocabulary: Lua src: '${LUA_SRC}'")

set(vocabulary_INCLUDES ${vocabulary_INCLUDES} 
	${CUSTOM_INCLUDES}
	${INCLUDES}
)

set(vocabulary_INCLUDES ${vocabulary_INCLUDES} PARENT_SCOPE)
message("vocabulary_INCLUDES: ${vocabulary_INCLUDES}")

if (NOT "${vocabulary_INCLUDES}" STREQUAL "")
	include_directories(${vocabulary_INCLUDES})
endif()

file(GLOB SRC CONFIGURE_DEPENDS "src/*")
set(SRC ${SRC})
file(GLOB HEADERS ${HEADERS} "include/*")

# Inherit parent sources logic

set(PARENT_SRC ${PARENT_SRC} ${SRC})
set(PARENT_SRC ${PARENT_SRC} PARENT_SCOPE)

if (INHERIT_PARENT_SRC)
	set(SRC ${PARENT_SRC})
	message("'vocabulary' project PARENT_SRC: ${PARENT_SRC}")
endif()

# End of Inherit parent sources logic

set(SRC main.cpp ${SRC})

message("'vocabulary' project SRC: ${SRC}")
message("'vocabulary' project HEADERS: ${HEADERS}")

add_executable (vocabulary main.cpp ${SRC} ${HEADERS})

target_link_libraries(vocabulary lualib)

set_target_properties(vocabulary PROPERTIES LINKER_LANGUAGE CXX)

configure_file(assets/random_words.lua ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)