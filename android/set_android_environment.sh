#!/bin/bash

function job()
{
	# local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	# cd "$THIS_DIR"
	source android_config.sh
	cd "$root_dir"

	source os.sh
	source log.sh

	local log_prefix="[set_android_environment.sh]: "

	[ -z "$ANDROID_HOME" ] && log_error "ANDROID_HOME is not set." && exit 1

	log "ANDROID_HOME: $ANDROID_HOME"
	log "ANDROID_NDK_HOME before: $ANDROID_NDK_HOME"
	log "JAVA_HOME before: $JAVA_HOME"
	# ndkPath is used instead of ANDROID_NDK_HOME
	export ANDROID_NDK_HOME=$ANDROID_HOME/ndk/25.1.8937393
	if is_windows; then
		export JAVA_HOME="C:/Program Files/Java/jdk-11.0.16.1"
	else
		export JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk-11.0.16.1.jdk/Contents/Home
	fi
	log "ANDROID_NDK_HOME after: $ANDROID_NDK_HOME"
	log "JAVA_HOME after: $JAVA_HOME"
	[ ! -d "$ANDROID_NDK_HOME" ] && log_error "Directory specified in ANDROID_NDK_HOME does not exist: '$ANDROID_NDK_HOME'" && exit 1
	[ ! -d "$JAVA_HOME" ] && log_error "Directory specified in JAVA_HOME does not exist: '$JAVA_HOME'" && exit 1
}

job $@
