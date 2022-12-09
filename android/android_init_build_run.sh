#!/bin/bash

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} android init build run script]: "

	source android_init.sh
	[ $? -ne 0 ] && return 1
	source android_build.sh
	[ $? -ne 0 ] && return 2
	source android_run.sh
	[ $? -ne 0 ] && return 3

	log_success "Finished everything" " -" " ---"
}

job $@