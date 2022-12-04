#!/bin/bash

get_dependencies()
{
	if [ ! -z "$1" ]; then 
		local enterDirectory=${PWD}	
		echo "Go to the source directory passed: '$1'"
		cd "$1" # go to the source directory passed
	fi

	source log.sh

	local folderName=${PWD##*/}

	local log_prefix="-- [$folderName get_dependencies script]: "

	log "Check for dependencies" " -"

	if [ ! -f "deps_config.sh" ]; then
		log "No dependencies" " -"
		cd "${enterDirectory}"
		return 0
	fi
	source deps_config.sh

	source deps_scenario.sh $@
	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "Error occured during the deps_scenario.sh execution " " -"
		[ ! -z "$enterDirectory" ] && cd "$enterDirectory"
		return 1
	fi

	[ ! -z "$enterDirectory" ] && cd "$enterDirectory"
}

get_dependencies $@