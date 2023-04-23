#!/bin/bash

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} android init build run script]: "

	source init.sh
	[ $? -ne 0 ] && return 1
	source build.sh
	[ $? -ne 0 ] && return 2
	source run.sh
	[ $? -ne 0 ] && return 3

	log_success "Finished everything" " -" " ---"
}

job $@