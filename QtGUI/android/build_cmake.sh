#!/bin/bash
# echo "PATH=$PATH"
# export PATH=/I/Dev/Qt/Tools/CMake_64/bin:$PATH

function job()
{
	source ../../log.sh
	source ../../os.sh
	source android_config.sh
	
	local log_prefix="-- [android/build_cmake.sh]: "

	if [ -z "$build_folder" ]; then
		log_error "build_folder is not set."
		exit 1
	fi

	cd ../$build_folder

	log_info "build_folder: '$build_folder'"
	local config=$(echo $1 | sed -e "s/\b\(.\)/\u\1/g")
	log_info "Building android for configuration '$config'"
	local cmake_path="I:/Dev/Qt/Tools/CMake_64/bin/cmake.exe"
	# if is_windows; then
	# 	cmake_path=$(cygpath -w "$cmake_path")
	# fi
	echo "cmake_path: '$cmake_path'"
	local cmd="$cmake_path --build . --config=$config --target all"
	echo "cmd: '$cmd'"
	# if is_windows; then
	# 	# Run cmd through PowerShell
	# 	cmd="powershell.exe -Command \"& { $cmd }\""
	# fi
	eval $cmd
	[ $? -ne 0 ] && log_error "$cmd FAILED." && exit 1 || log_success "$cmd SUCCEEDED."
}

job $@