cmake_minimum_required(VERSION 3.21.1)

project(vocabulary LANGUAGES CXX)

set(BUILD_QDS_COMPONENTS ON CACHE BOOL "Build design studio components")

set(CMAKE_VERBOSE_MAKEFILE ON)

enable_language(CXX)

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

option(LOG_ON "Turn on logging" ON)


macro(setup_module)
    setup_qt_cmake_prefix_path()

    message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
    message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

    find_package(QT NAMES Qt6 COMPONENTS Gui Qml Quick Widgets QuickControls2)
    find_package(Qt6 COMPONENTS Core Gui Qml Quick Widgets QuickControls2 REQUIRED)

    # To build this application you need Qt 6.2.0 or higher
    message("Qt6_VERSION: ${Qt6_VERSION}")

    if (Qt6_VERSION VERSION_LESS 6.2.0)
        message(FATAL_ERROR "You need Qt 6.2.0 or newer to build the application.")
    endif()

    # abstract_ui_qt dependency
	add_dependency_module(${DEPS}/abstract_ui/qt abstract_ui_qt)
    module_message("abstract_ui_qt_INCLUDES: ${abstract_ui_qt_INCLUDES}")

    # Utils dependency
	set(UTILS_DIR "${DEPS}/Utils")

	# Core dependency
	add_dependency_module(${CMAKE_SOURCE_DIR}/../core vocabulary_core)
	module_message("vocabulary_core_INCLUDES: ${vocabulary_core_INCLUDES}")
    module_add_includes(
        ${vocabulary_core_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
    # make available includes like core/include/something
    setup_module_includes()
    set_headers()
    add_src(
        ${HEADERS} # for IDE
    )
    setup_src()
    module_message("CMAKE_PROJECT_NAME: '${CMAKE_PROJECT_NAME}'")
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
        Qt${QT_VERSION_MAJOR}::QuickControls2 
    )

    if (${BUILD_QDS_COMPONENTS})
        include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
    endif ()

    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        module_message("Enable QML Debugging")
		target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE QT_QML_DEBUG)
	endif()

    if (WIN32)
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${MODULE_NAME}> $<TARGET_FILE_DIR:${MODULE_NAME}>
            COMMAND_EXPAND_LISTS
        )
    endif()
endmacro(setup_module)

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
