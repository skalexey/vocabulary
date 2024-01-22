#!/bin/bash

# This script follows instructions given in the README-android.md by the link:
# https://github.com/libsdl-org/SDL/blob/main/docs/README-android.md

job()
{
	# Load common variables
	source android_config.sh

	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	# Load environment variables
	source $THIS_DIR/set_android_environment.sh
	
	# Go to the root directory
	cd "$root_dir"

	source log.sh
	local log_prefix="-- [${folderName} android build script]: "

	source file_utils.sh

	# Setup logger
	local folderName=${PWD##*/}

	# Set project's environment variables
	source external_config.sh

	# Uninstall the app first
	# adb uninstall "$app"

	# Store the absolute path to the current directory and go to the android project 
	local root_dir="${PWD}"
	local android_dir="$root_dir/$android_dir"

	cd $proj

	local build_config="Debug"

	for arg in "$@" 
	do
		echo "arg[$argIndex]: '$arg'"
		arg=$(echo $arg | tr '[:upper:]' '[:lower:]')
		if [[ "$arg" == "release" ]]; then
			log "'release' option passed. Set Release build type" " --"
			local build_config="Release"
		fi
		local argIndex=$((argIndex + 1))
	done

	local app_dir="$root_dir/$proj/app"

	if [[ "$build_config" == "Release" ]]; then
		if [ ! -f "$app_dir/$key" ]; then
			keytool -genkey -v -keystore "$app_dir/$key" -keyalg RSA -keysize 2048 -validity 10000 -alias my-alias
			[ $? -ne 0 ] && log_error "Error while generating the key" && return 2
		else
			log_info "Key '$key' already exists"
		fi
		[ ! -f "$root_dir/.gitignore" ] && echo "" >> "$root_dir/.gitignore"
		local search_res=$(file_search "$root_dir/.gitignore" "$key")
		[ $search_res -eq -1 ] && echo "$key" >> "$root_dir/.gitignore" && log_info "Key is ignored for git (added to .gitignore)"
	fi

	# Start android build
	# Go back to the root dir
	cd "$android_dir"

	log_info "Start building the project"
	
	# Run local build script
	./build_project.sh $@

	[ $? -ne 0 ] && log_error "Error while building" && return 1
	
	log_success "Finished build" " -" " ---"
}

job $@