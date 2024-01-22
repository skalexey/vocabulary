#!/bin/bash

function job()
{
	local current_dir=${PWD}
	echo "current_dir: '$current_dir'"
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR/.."
	source log.sh
	local log_prefix="[build_and_deploy.sh]: "
	local configuration="Release"
	# iterate arguments case-insensitive
	for arg in "$@"; do
		arg=$(echo "$arg" | tr '[:upper:]' '[:lower:]')
		if [ "$arg" == "debug" ]; then
			log_info "debug argument passed"
			configuration="Debug"
		fi
	done
	log_warning "Build and deploy '$configuration' configuration"
	./build.sh "$THIS_DIR" $configuration
	[ $? -ne 0 ] && log_error " --- Errors during building" && exit 1
	$THIS_DIR/deploy.sh $@
	[ $? -ne 0 ] && log_error " --- Errors during deploying" && exit 1
	log_success " --- All done"
}

job $@