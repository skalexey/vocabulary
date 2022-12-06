#!/bin/bash

# This script follows instructions given in the README-android.md by the link:
# https://github.com/libsdl-org/SDL/blob/main/docs/README-android.md

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	source set_android_environment.sh

	# Load common variables
	source android_config.sh

	# Setup logger
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} android init script]: "

	[ -d "$proj" ] && rm -rf "$proj"

	log "Create the project" " -" " ---"

	source external_config.sh

	local SDL="$vocabulary_deps/SDL"

	# Copy the SDL android project template
	cp -r "$SDL/android-project" "$proj"

	# Include before switching the directory
	source file_utils.sh

	local root_path=${PWD}
	# Go to the newly created project directory
	cd "$proj"

	# Remove src folder as it is not needed while we are using CMake project
	rm -rf "app/jni/src"

	# Configure
	cp "$root_path/build.gradle.replace" "app/build.gradle"
	cp "$root_path/jni_CMakeLists.txt.replace" "app/jni/CMakeLists.txt"
	cp "$root_path/keystore.properties.put" "app/keystore.properties"
	echo "keystore.properties" >> app/.gitignore
	
	# Go back to the root directory
	cd "$root_path"

	log_success "Finished project creation" " -" " ---"
}

job $@