#!/bin/bash

function update_build_system()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"
	
	local folderName=${THIS_DIR##*/}

	source log.sh
	local log_prefix="[$folderName update_build_system]: "

	./update_scripts.sh
	./update_cmake_modules.sh

	[ $? -ne 0 ] && log_error "Error while updating build system" && return 2

	log_success "Done"
}

update_build_system $@