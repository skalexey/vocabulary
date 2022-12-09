#!/bin/bash

root_dir=..
android_dir="android"

function get_app_activity_name()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR/$root_dir"

	# Include before switching the directory
	source file_utils.sh

	# Get the package name
	local classname=$(file_regex $android_dir/MainActivity.java ".*class\s+([^\s]+)\s+extends.*")
	if [ -z "$classname" ] || [ "$classname" == "-1" ]; then
		log_error "Failed to get the activity class name. Check if it is present and has an appropriate format"
		return 1
	fi
	echo $classname
}

app=com.skalexey.vocabulary
classname=$(get_app_activity_name)
appname="Vocabulary"
proj="android-project"
key="my-release-key.jks"