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
	[ -z "$config" ] &&	config="Debug"

	log_info "Building android for configuration '$config'"
	local cmd="$cmake_path --build . --config=$config --target all"
	log_info "Build command: '$cmd'"
	eval $cmd
	[ $? -ne 0 ] && log_error "$cmd FAILED." && exit 1 || log_success "$cmd SUCCEEDED."

	cmd="$deployqt_path --input android-vocabulary-deployment-settings.json --output android-build --android-platform android-31 --jdk $JAVA_HOME --gradle"

	log_info "APK Generation command: '$cmd'"
	# Execute command 
	eval $cmd
	[ $? -ne 0 ] && log_error "$cmd FAILED." && exit 1 || log_success "$cmd SUCCEEDED."
}

job $@