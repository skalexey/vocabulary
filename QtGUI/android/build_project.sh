#!/bin/bash
# echo "PATH=$PATH"
# export PATH=/I/Dev/Qt/Tools/CMake_64/bin:$PATH

function job()
{
	source ../../log.sh
	local log_prefix="-- [android/build.sh]: "
	local configure_script_name="configure_cmake.sh"
	local build_script_name="build_cmake.sh"
	echo ${PWD}/$configure_script_name
	./$configure_script_name
	[ $? -ne 0 ] && log_error "$configure_script_name failed." && exit 1 || log_success "$configure_script_name succeeded."
	./$build_script_name
	[ $? -ne 0 ] && log_error "$build_script_name failed." && exit 1 || log_success "$build_script_name succeeded."
}

job $@