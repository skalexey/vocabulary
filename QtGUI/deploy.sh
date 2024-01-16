#!/bin/bash

source ../os.sh

function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"
	source ../log.sh
	local log_prefix="[deploy.sh]: "
	if is_windows; then
		# Run deploy.ps1
		powershell.exe -ExecutionPolicy Bypass -File "deploy.ps1"
		if [ $? -ne 0 ]; then
			log_error " --- Errors during deploying"
			exit 1
		fi
		exit $?
	elif is_mac; then
		local deploy_dir="/Applications"
	else
		local deploy_dir="/usr/bin"
	fi

	if [ $? -ne 0 ]; then
		log_error " --- Errors during initial phase"
		exit 1
	fi

	if [ ! -d "$deploy_dir" ]; then
		log_info "Creating directory '$deploy_dir'"
		mkdir -p "$deploy_dir"
	fi

	cp Build-cmake-Release/Debug/vocabulary "$deploy_dir"
	[ $? -ne 0 ] && log_error " --- Errors during deploying at '$deploy_dir'" || log_success " --- Deployed successfully at '$deploy_dir'"
}

job $@