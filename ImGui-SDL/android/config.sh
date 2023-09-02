#!/bin/bash

root_dir=..
android_dir="android"
app=com.skalexey.vocabulary

function parse_activity_name()
{
	echo $(file_regex $1 ".*class\s+([^\s]+)\s+extends.*")
}

function get_app_activity_name()
{
	source log.sh
	source file_utils.sh

	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR/$root_dir"
	
	local log_prefix="-- [android_config.sh]: "

	# Include before switching the directory
	

	# Get the package name
	if [ -d "$android_dir/app" ]; then
		local appdir="${app//"."/"/"}" 
		local classname=$android_dir/app/src/$appdir/MainActivity.java
		if [ $? -ne 0 ]; then
			log_error "Failed to get the activity class name. Check if it is present and has an appropriate format"
			return 1
		fi
	else
		local classname=$(parse_activity_name $android_dir/MainActivity.java)
		if [ -f "$android_dir/MainActivity.java" ]; then
			if [ -z "$classname" ] || [ "$classname" == "-1" ]; then
				log_error "Failed to get the activity class name. Check if it is present and has an appropriate format"
			fi
		fi
	fi
	echo $classname
}

classname=$(get_app_activity_name)
appname="Vocabulary"
proj="android-project"
key="my-release-key.jks"