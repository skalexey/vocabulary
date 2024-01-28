#!/bin/bash

function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	source ../../os.sh
	source ../../log.sh
	source android_config.sh
	
	local log_prefix="-- [android/configure_cmake.sh]: "

	local qt_dir="$QT_DIR"
	[ -z "$qt_dir" ] && log_error "QT_DIR is not set." && exit 1

	[ ! -f "$ninja_path" ] && log_error "File specified as a Ninja executable does not exist: '$ninja_path'." && exit 1
	# Check if a file in cmake_path exists only if it does not equals "cmake"
	[ "$cmake_path" != "cmake" ] && [ ! -f "$cmake_path" ] && log_error "File specified as a CMake executable does not exist: '$cmake_path'" && exit 2
	
	local qt_chainload_toolchain_file="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake"
	local cmake_toolchain_file="$qt_dir/android_arm64_v8a/lib/cmake/Qt6/qt.toolchain.cmake"

	
	if [ -z "$build_folder" ]; then
		log_error "build_folder is not set."
		exit 3
	fi
	# if is_windows; then
	# 	ninja_path=$(cygpath -w "$ninja_path")
	# 	cmake_path=$(cygpath -w "$cmake_path")
	# 	qt_chainload_toolchain_file=$(cygpath -w "$qt_chainload_toolchain_file")
	# 	cmake_toolchain_file=$(cygpath -w "$cmake_toolchain_file")
	# 	ANDROID_NDK_HOME=$(cygpath -w "$ANDROID_NDK_HOME")
	# 	ANDROID_HOME=$(cygpath -w "$ANDROID_HOME")
	# fi
	# rm -rf ../$build_folder

	log "configure_cmake.sh: ANDROID_NDK_HOME: '$ANDROID_NDK_HOME'"
	log "configure_cmake.sh: ANDROID_HOME: '$ANDROID_HOME'"
	log "ninja_path: '$ninja_path'"
	log "cmake_path: '$cmake_path'"
	log "qt_chainload_toolchain_file: '$qt_chainload_toolchain_file'"
	log "cmake_toolchain_file: '$cmake_toolchain_file'"
	log "QT_DIR: '$QT_DIR'"

	# QT_DIR should be set to the Qt version installation directory
	# /I/Dev/Qt/Tools/CMake_64/bin/cmake.exe -S .. -B ../Build-cmake-android -DCMAKE_TOOLCHAIN_FILE=$QT_DIR/android_arm64_v8a/lib/cmake/Qt6/qt.toolchain.cmake -DQT_CHAINLOAD_TOOLCHAIN_FILE:PATH=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake -DCMAKE_FIND_DEBUG_MODE=FALSE -DQT_DEBUG_FIND_PACKAGE=OFF -DCMAKE_GENERATOR:STRING=Ninja -DCMAKE_MAKE_PROGRAM:PATH=I:/Dev/Qt/Tools/Ninja/ninja.exe -DANDROID_SDK_ROOT:PATH=$ANDROID_HOME -DANDROID_NDK:PATH=$ANDROID_NDK_HOME -DANDROID_PLATFORM:STRING=android-23 -DQT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON -DANDROID_USE_LEGACY_TOOLCHAIN_FILE:BOOL=OFF -DCMAKE_BUILD_TYPE:STRING=Debug

	# Copied from qt_build_cmake.sh
	local cmd="$cmake_path -S .. -B ../$build_folder -DCMAKE_GENERATOR:STRING=Ninja -DANDROID_PLATFORM:STRING=android-23 -DANDROID_NDK:PATH=$ANDROID_NDK_HOME -DQT_CHAINLOAD_TOOLCHAIN_FILE:FILEPATH=$qt_chainload_toolchain_file -DANDROID_USE_LEGACY_TOOLCHAIN_FILE:BOOL=OFF -DANDROID_ABI:STRING=arm64-v8a -DANDROID_STL:STRING=c++_shared -DQT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON -DANDROID_SDK_ROOT:PATH=$ANDROID_HOME -DCMAKE_MAKE_PROGRAM=$ninja_path -DCMAKE_TOOLCHAIN_FILE=$cmake_toolchain_file"

	# if is_windows; then
	# 	Run cmd through PowerShell
	# 	cmd="powershell.exe -Command \"& { $cmd }\""
	# fi

	log_info "Configure command: '$cmd'"
	echo "configure_cmake.sh: cmd: '$cmd'" > "$THIS_DIR/configure_cmake_cmd.log"

	eval $cmd
	[ $? -ne 0 ] && log_error "cmake configure command failed." && exit 4 || log_success "cmake configure command succeeded."
}

job $@