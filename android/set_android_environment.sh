#!/bin/bash

function job()
{
	# local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	# cd "$THIS_DIR"
	source android_config.sh
	cd "$root_dir"
	source os.sh

	echo "ANDROID_HOME before: $ANDROID_HOME"
	echo "ANDROID_NDK_HOME before: $ANDROID_NDK_HOME"
	echo "JAVA_HOME before: $JAVA_HOME"
	export ANDROID_HOME=~/bin/android/sdk
	# ndkPath is used instead of ANDROID_NDK_HOME
	export ANDROID_NDK_HOME=~/bin/android/sdk/ndk/25.1.8937393
	if is_windows; then
		export JAVA_HOME="C:/Program Files/Java/jdk-11.0.16.1"
	else
		export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.16.1.jdk/Contents/Home
	fi
	echo "ANDROID_HOME after: $ANDROID_HOME"
	echo "ANDROID_NDK_HOME after: $ANDROID_NDK_HOME"
	echo "JAVA_HOME after: $JAVA_HOME"

	cd "$THIS_DIR"
}

job $@
