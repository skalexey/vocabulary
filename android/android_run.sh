#!/bin/bash

job()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd "$THIS_DIR"

	# Load common variables
	source android_config.sh

	adb shell am start "$app/$app.$classname"
}

job $@