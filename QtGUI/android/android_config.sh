#!/bin/bash

root_dir="$(cd ../.. && pwd)"
android_dir="QtGUI/android"
app=org.qtproject.example.vocabulary
classname="org.qtproject.qt.android.bindings.QtActivity"
appname="Vocabulary"
proj="QtGUI/android" # temporarily set to the control directory
key="my-release-key.jks"
build_folder="Build-cmake-android"
qt_dir="$QT_DIR"
[ -z "$qt_dir" ] && log_error "QT_DIR is not set." && exit 1

if is_windows; then
    # Windows-style paths
    export JAVA_HOME="C:/Program Files/Java/jdk-17"
    qt_dir=$(cygpath "$qt_dir")
    cmake_path="${qt_dir}/../Tools/CMake_64/bin/cmake.exe"
    deployqt_path="${qt_dir}/../Tools/QtCreator/bin/androiddeployqt.exe"
    ninja_path="${qt_dir}/../Tools/Ninja/ninja.exe"
else
    export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-17.jdk/Contents/Home
    cmake_path="${qt_dir}/../Tools/CMake/CMake.app/Contents/bin/cmake" #cmake #/Users/skalexey/Library/Android/sdk/cmake/3.22.1/bin/cmake
    ninja_path="${qt_dir}/../Tools/Ninja/ninja"
    deployqt_path="${qt_dir}/macos/bin/androiddeployqt"
fi