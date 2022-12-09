#!/bin/bash

function job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"
	source android_config.sh
	cd "$root_dir"

	source os.sh

	echo "ANDROID_SDK_ROOT before: $ANDROID_SDK_ROOT"
	echo "ANDROID_NDK_ROOT before: $ANDROID_NDK_ROOT"
	echo "JAVA_HOME before: $JAVA_HOME"
	export ANDROID_SDK_ROOT=~/bin/android/sdk
	export ANDROID_NDK_ROOT=~/bin/android/sdk/ndk/25.1.8937393
	if is_windows; then
		export JAVA_HOME="C:/Program Files/Java/jdk-11.0.16.1"
	else
		export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.16.1.jdk/Contents/Home
	fi
	echo "ANDROID_SDK_ROOT after: $ANDROID_SDK_ROOT"
	echo "ANDROID_NDK_ROOT after: $ANDROID_NDK_ROOT"
	echo "JAVA_HOME after: $JAVA_HOME"

	cd "$THIS_DIR"
}

job $@
