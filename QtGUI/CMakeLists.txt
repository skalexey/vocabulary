cmake_minimum_required(VERSION 3.21.1)

set(BUILD_QDS_COMPONENTS ON CACHE BOOL "Build design studio components")

set(CMAKE_PREFIX_PATH "I:/Dev/Qt/6.5.0/android_arm64_v8a")
set(QT_HOST_PATH "I:/Dev/Qt/6.5.0/msvc2019_64")
# message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

project(QtGUIApp LANGUAGES CXX)

#find_package(Threads REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable generating debug information for Qt libraries
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Enable generating debug information for Qt libraries in Release mode as well
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")

# include(D:/Content/Dev/Qt/6.5.1/android_arm64_v8a/lib/cmake/Qt6/Qt6Config.cmake)
# set(CMAKE_PREFIX_PATH "i:/Dev/Qt/6.5.0/msvc2019_64")


find_package(QT NAMES Qt6 COMPONENTS Gui Qml Quick)
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Widgets)

# To build this application you need Qt 6.2.0 or higher
if (Qt6_VERSION VERSION_LESS 6.2.0)
    message(FATAL_ERROR "You need Qt 6.2.0 or newer to build the application.")
endif()

option(LOG_ON "Turn on logging" ON)

macro(setup_module)
    # Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")

	# Core dependency
	add_dependency_module(${CMAKE_SOURCE_DIR}/../core vocabulary_core)
	module_message("vocabulary_core_INCLUDES: ${vocabulary_core_INCLUDES}")
	module_add_includes(${vocabulary_core_INCLUDES})
    # make available includes like core/include/something
	module_add_includes(${CMAKE_CURRENT_SOURCE_DIR}/..)
    setup_module_includes()
    set_headers()
    add_src(
        ${UTILS_DIR}/src/ui/qt/node.cpp
        ${UTILS_DIR}/src/ui/qt/app.cpp
		${UTILS_DIR}/src/ui/qt/widget.cpp
		${UTILS_DIR}/src/ui/qt/widgets/text_input.cpp
		${UTILS_DIR}/src/ui/qt/widgets/text.cpp
		${UTILS_DIR}/src/ui/qt/widgets/label.cpp
		${UTILS_DIR}/src/ui/qt/widgets/button.cpp
		${UTILS_DIR}/src/ui/qt/widgets/dialog.cpp
		${UTILS_DIR}/src/ui/qt/widget_factory.cpp
		${UTILS_DIR}/src/ui/qt/widgets/dialogs/dialog_with_buttons.cpp
		${UTILS_DIR}/src/ui/qt/widgets/dialogs/dialog_yes_no.cpp
		${UTILS_DIR}/src/ui/qt/widgets/dialogs/dialog_message.cpp
		${UTILS_DIR}/src/ui/qt/widgets/dialogs/dialog_input_text.cpp
        ${UTILS_DIR}/include/utils/ui/qt/widgets/button_model.h
        ${UTILS_DIR}/src/ui/qt/widgets/button_model.cpp
        ${UTILS_DIR}/include/utils/ui/qt/widgets/text_input_model.h
        ${UTILS_DIR}/src/ui/qt/widgets/text_input_model.cpp
        ${HEADERS} # for IDE
    )
    setup_src()
    qt_add_executable(${CMAKE_PROJECT_NAME} ${SRC})
    module_message("DEPENDENCY_LIBRARIES: ${DEPENDENCY_LIBRARIES}")
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${DEPENDENCY_LIBRARIES})
	# copy_runtime_deps()

    if (${QT_VERSION_MINOR} GREATER_EQUAL 3)

    qt6_standard_project_setup()

    endif()

    qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
        PREFIX "/"
        FILES
            qtquickcontrols2.conf
    )

    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Widgets
    )

    if (${BUILD_QDS_COMPONENTS})
        include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
    endif ()

    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE QT_QML_DEBUG)
	endif()
    
endmacro(setup_module)

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
