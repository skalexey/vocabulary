#!/bin/bash

function job()
{
	source ../../log.sh
	source ../../os.sh
	source android_config.sh
	
	local log_prefix="-- [android/deploy.sh]: "

	if [ -z "$build_folder" ]; then
		log_error "build_folder is not set."
		exit 1
	fi

	cd ../$build_folder

	log_info "build_folder: '$build_folder'"
	local config=$(echo $1 | sed -e "s/\b\(.\)/\u\1/g")
	[ -z "$config" ] &&	config="Debug"

	log_info "Deploying android for configuration '$config'"
	local device_id=$($root_dir/android/get_device_id.sh)
	local retcode=$?
	[ $retcode -ne 0 ] && log_error "Failed to get device id. Error code: $retcode" && exit 2
	[ -z "$device_id" ] && log_error "Device id is empty." && exit 3

	cmd="$deployqt_path --no-build --verbose --input android-vocabulary-deployment-settings.json --output android-build --gradle --reinstall --device $device_id"

	log_info "APK Deployment command: '$cmd'"
	# Execute command 
	eval $cmd
	[ $? -ne 0 ] && log_error "$cmd FAILED." && exit 1 || log_success "$cmd SUCCEEDED."
}

job $@
