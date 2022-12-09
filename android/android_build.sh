#!/bin/bash

# This script follows instructions given in the README-android.md by the link:
# https://github.com/libsdl-org/SDL/blob/main/docs/README-android.md

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	# Load common variables
	source android_config.sh

	# Load environment variables
	source set_android_environment.sh
	
	# Go to the root directory
	cd "$root_dir"

	source file_utils.sh

	# Setup logger
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} android build script]: "

	# Set project's environment variables
	source external_config.sh

	# Uninstall the app first
	# adb uninstall "$app"

	# Store the current directory and go to the android project 
	local root_dir="${PWD}"
	local android_dir="$root_dir/$android_dir"

	cd $proj

	local build_config="Debug"

	for arg in "$@" 
	do
		echo "arg[$argIndex]: '$arg'"
		if [[ "$arg" == "release" ]]; then
			log "'release' option passed. Set Release build type" " --"
			local build_config="Release"
		fi
		local argIndex=$((argIndex + 1))
	done

	if [[ "$build_config" == "Release" ]]; then
		if [ ! -f "$android_dir/$key" ]; then
			keytool -genkey -v -keystore "$android_dir/$key" -keyalg RSA -keysize 2048 -validity 10000 -alias my-alias
			[ $? -ne 0 ] && log_error "Error while generating the key" && return 2
		else
			log_info "Key '$key' already exists"
		fi
		[ ! -f "$root_dir/.gitignore" ] && echo "" >> "$root_dir/.gitignore"
		local search_res=$(file_search "$root_dir/.gitignore" "$key")
		[ $search_res -eq -1 ] && echo "$key" >> "$root_dir/.gitignore" && log_info "Key is ignored for git (added to .gitignore)"
		cp "$android_dir/$key" "app/"
	fi

	# Start android build
	./gradlew install$build_config
	[ $? -ne 0 ] && log_error "Error while building" && return 1

	# Go back to the root dir
	cd "$android_dir"
	
	log_success "Finished build" " -" " ---"
}

job $@