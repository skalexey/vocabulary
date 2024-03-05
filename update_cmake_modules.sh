#!/bin/bash

function update_cmake_modules()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	source log.sh
	local log_prefix="[update_cmake_modules]: "

	[ -z $1 ] && log_error "No directory provided" && return 1
	[ ! -d $1 ] && log_error "Non-existent directory provided: '$1'" && return 2

	source file_utils.sh
	local dir=$(full_path "$1")
	[ $? -ne 0 ] && log_error "Error while getting full path" && return 3
	source automation_config.sh
	[ $? -ne 0 ] && echo "Get automation_config.sh manually for the first time. It contains paths to dependent directories" && return 3
	source $automation_dir/templates/templates_config.sh
	[ $? -ne 0 ] && echo "Get automation_config.sh manually for the first time. It contains paths to dependent directories" && return 3
	local templates_modules_dir=$templates_dir/CMake/Modules/modules
	local target_modules_dir=$dir/cmake_modules
	local list=$(ls $templates_modules_dir)
	if [ ! -d $dir/cmake_modules ]; then
		mkdir $dir/cmake_modules
	fi

	[ $? -ne 0 ] && log_error "Error while creating cmake_modules directory" && return 4
	log_warning "Copying cmake modules to '$target_modules_dir'..."
	for file in $list; do
		log_info "Copying module '$file'"
		cp "$templates_modules_dir/$file" $target_modules_dir/
	done

	[ $? -ne 0 ] && log_error "Error while delivering cmake modules" && return 5

	log_success "Done"

	return 0
}

update_cmake_modules $@
