#!/bin/bash

function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd $THIS_DIR/..
	./build.sh "$THIS_DIR" release
	local build_result=$?
	source log.sh
	local log_prefix="[build_and_deploy.sh]: "
	if [ $? -ne 0 ]; then
		log_error " --- Errors during building"
		exit 1
	fi
	cd $THIS_DIR
	./deploy.sh
	if [ $? -ne 0 ]; then
		log_error " --- Errors during deploying"
		exit 1
	fi
	log_success " --- All done"
}

job $@