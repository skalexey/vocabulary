#!/bin/bash
# echo "PATH=$PATH"
# export PATH=/I/Dev/Qt/Tools/CMake_64/bin:$PATH

local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# /I/Dev/Qt/6.5.0/android_arm64_v8a/bin/qt-cmake

# rm -rf ../Build-cmake-android

echo "configure_cmake.sh: ANDROID_NDK_HOME: '$ANDROID_NDK_HOME'"
echo "configure_cmake.sh: ANDROID_HOME: '$ANDROID_HOME'"

/I/Dev/Qt/Tools/CMake_64/bin/cmake.exe -S .. -B ../Build-cmake-android -DCMAKE_TOOLCHAIN_FILE=I:/Dev/Qt/6.5.0/android_arm64_v8a/lib/cmake/Qt6/qt.toolchain.cmake -DQT_CHAINLOAD_TOOLCHAIN_FILE:PATH=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_FIND_DEBUG_MODE=FALSE -DQT_DEBUG_FIND_PACKAGE=OFF -DCMAKE_GENERATOR:STRING=Ninja -DCMAKE_MAKE_PROGRAM:PATH=I:/Dev/Qt/Tools/Ninja/ninja.exe -DANDROID_SDK_ROOT:PATH=$ANDROID_HOME -DANDROID_NDK:PATH=$ANDROID_NDK_HOME -DANDROID_PLATFORM:STRING=android-23 -DQT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON -DANDROID_USE_LEGACY_TOOLCHAIN_FILE:BOOL=OFF -DCMAKE_BUILD_TYPE:STRING=Debug
