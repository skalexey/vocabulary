#!/bin/bash

# This script follows instructions given in the README-android.md by the link:
# https://github.com/libsdl-org/SDL/blob/main/docs/README-android.md

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	# Load common variables
	source android_config.sh

	# Setup logger
	local folderName=${PWD##*/}

	local android_dir=${PWD}

	# Go to the root directory
	cd "$root_dir"

	source log.sh
	local log_prefix="-- [${folderName} android init script]: "

	[ -d "$proj" ] && rm -rf "$proj" || log_info "Directory '$proj' does not exist. Will create it"
	[ $? -ne 0 ] && log_error "Error while removing the project directory" && return 1
	
	log "Create the project" " -" " ---"

	source external_config.sh

	local SDL="$build_deps/SDL"

	# Copy the SDL android project template
	cp -r "$SDL/android-project" "$proj"

	# Include before switching the directory
	source file_utils.sh

	# Get the package name
	log_info "App package: $app"

	# Get the activity class name
	log_info "App activity name: $classname"

	# Go to the newly created project directory
	cd "$proj"

	# Remove src folder as it is not needed while we are using CMake project
	rm -rf "app/jni/src"

	# Configure
	cp "$android_dir/build.gradle.replace" "app/build.gradle"
	cp "$android_dir/jni_CMakeLists.txt.replace" "app/jni/CMakeLists.txt"
	cp "$android_dir/keystore.properties.put" "app/keystore.properties"
	echo "keystore.properties" >> app/.gitignore

	# Setup the app package
	appdir="${app//"."/"/"}" 
	log_info "Create appdir '$appdir' at 'app/src/main/java'"
	appdir_path="app/src/main/java/$appdir"
	mkdir -p "$appdir_path"
	cp "$android_dir/MainActivity.java" "$appdir_path/"
	file_replace "$appdir_path/MainActivity.java" "my.app.pack" "$app"

	# Replace the package name in SDL package configuration
	file_replace "app/src/main/AndroidManifest.xml" "SDLActivity" "$classname"
	file_replace "app/src/main/AndroidManifest.xml" "org.libsdl.app" "$app"
	file_replace "app/src/main/AndroidManifest.xml" "org.libsdl.app" "$app"
	file_replace "app/build.gradle" "org.libsdl.app" "$app"
	
	# Setup resources
	rm -rf "app/src/main/res/"
	cp -r "$android_dir/res" "app/src/main/"
	cp "$android_dir/ic_launcher-playstore.png" "app/src/main/"
	file_replace "app/src/main/res/values/strings.xml" "Game" "$appname"
	
	# Go back to the root directory
	cd "$android_dir"

	log_success "Finished project creation" " -" " ---"
}

job $@