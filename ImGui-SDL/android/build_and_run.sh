#!/bin/bash

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	local folderName=${PWD##*/}
	source config.sh
	source log.sh
	
	local log_prefix="-- [${folderName} android build and run script]: "

	source build.sh
	source run.sh

	log_success "Finished everything" " -" " ---"
}

job $@