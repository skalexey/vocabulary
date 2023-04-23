#!/bin/bash

function update_scripts()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"
	
	source automation_config.sh
	[ $? -ne 0 ] && echo "Get automation_config.sh manually for the first time. It contains paths to dependent directories" && return 3
	
	cp "$automation_dir/automation_config.sh" .
	cp "$scripts_dir/include/log.sh" .
	cp "$scripts_dir/include/os.sh" .

	source log.sh
	local log_prefix="[update_scripts]: "

	[ $? -ne 0 ] && log_error "Error while delivering files" && return 1

	log_success "Done"
}

update_scripts $@