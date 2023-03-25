#!/usr/bin/bash

function get_log()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	cd $THIS_DIR
	source $THIS_DIR/../log.sh
	local log_prefix="[get_log]: "
	local log_fname="vocabulary_log.txt"
	local adb_devices_output=$(adb devices)
	local device_id=$(echo "$adb_devices_output" | grep -v "List of devices attached" | head -n 1 | cut -f 1)
	log_info "Select device '$device_id'"
	# adb -s $device_id exec-out run-as com.skalexey.vocabulary pull /data/data/com.skalexey.vocabulary/cache/vocabulary_log.txt $THIS_DIR/
	adb -s $device_id exec-out run-as com.skalexey.vocabulary cat cache/$log_fname > $THIS_DIR/$log_fname
	# adb -s $device_id root
	# adb -s $device_id pull /data/data/com.skalexey.vocabulary/cache/vocabulary_log.txt $THIS_DIR/
	[ $? -ne 0 ] && log_error "adb pull failed" && return 1
	code vocabulary_log.txt
}

get_log $@