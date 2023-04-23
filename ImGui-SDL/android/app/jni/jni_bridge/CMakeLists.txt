cmake_minimum_required(VERSION 3.21)

project(JNI_BRIDGE C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC "src/*")

message("jni_bridge CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(include)
set(JNI_BRIDGE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

add_library(jni_bridge STATIC ${SRC})
target_link_libraries(jni_bridge PRIVATE SDL2)