cmake_minimum_required(VERSION 3.21.1)

project(QtGUIApp LANGUAGES CXX)
# set(CMAKE_PROJECT_NAME QtGUIApp) #TODO: remove this
set(BUILD_QDS_COMPONENTS ON CACHE BOOL "Build design studio components")

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

set(CMAKE_VERBOSE_MAKEFILE ON)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "I:/Dev/Qt/6.5.0/android_arm64_v8a")
# set(QT_HOST_PATH "I:/Dev/Qt/6.5.0/msvc2019_64")


# set(QT_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake")
# set(Qt6_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake")
# message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# set(Qt6_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6")
# set(Qt6Core_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Core")
# set(Qt6Qml_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Qml")
# set(Qt6QmlIntegration_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QmlIntegration")
# set(Qt6Network_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Network")
# set(Qt6Quick_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Quick")
# set(Qt6Gui_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Gui")
# set(Qt6QmlModels_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QmlModels")
# set(Qt6OpenGL_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6OpenGL")
# set(Qt6Widgets_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6Widgets")



# set(Qt6QuickControls2_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QuickControls2")
# set(Qt6QuickTemplates2_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QuickTemplates2")
# set(Qt6QuickControls2Models_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QuickControls2Models")
# set(Qt6QuickControls2Utils_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QuickControls2Utils")
# set(Qt6QuickWidgets_DIR "I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6QuickWidgets")


#


enable_language(CXX)

#find_package(Threads REQUIRED)
# find_package(GLESv2 REQUIRED)

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

# include(i:/Dev/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake)
find_package(QT NAMES Qt6 COMPONENTS Gui Qml Quick Widgets QuickControls2)
find_package(Qt6 COMPONENTS Core Gui Qml Quick Widgets QuickControls2 REQUIRED)

# To build this application you need Qt 6.2.0 or higher
message("Qt6_VERSION: ${Qt6_VERSION}")

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
    module_add_includes(
        ${vocabulary_core_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
    # make available includes like core/include/something
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
    module_message("CMAKE_PROJECT_NAME: '${CMAKE_PROJECT_NAME}'")
    qt_add_executable(${CMAKE_PROJECT_NAME} ${SRC})
    module_message("DEPENDENCY_LIBRARIES: ${DEPENDENCY_LIBRARIES}")
    target_link_libraries(QtGUIApp PRIVATE ${DEPENDENCY_LIBRARIES})
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
    
endmacro(setup_module)

include(cmake_modules/modules.cmake)
modules_include_all(cmake_modules)
setup_module_project()
