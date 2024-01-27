#!/bin/bash

build()
{
	local folderName=${PWD##*/}
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	source $THIS_DIR/log.sh
	local log_prefix="-- [${folderName} build script]: "

	log "Build for OS: $OSTYPE" " -" " ---"

	if [ -f "$THIS_DIR/deps_config.sh" ]; then
		source $THIS_DIR/deps_config.sh
	fi

	local buildFolderPrefix="Build"
	local onlyLibArg=" "
	local cmakeTestsArg=" "
	local cmakeGppArg=" "
	local buildConfig="Debug"
	local logArg=" -DLOG_ON=ON"
	local build=""
	local rootDirectory="."
	local onlyConfig=false
	local reconfigure=false
	local extraArg=" "
	local extraArgWin=$extraArg
	local extraArgMac=$extraArg
	
	source $THIS_DIR/os.sh

	if is_windows; then
		local generatorArg=" "
		local extraArg=$extraArgWin
	elif is_mac; then
		local generatorArg=" -GXcode"
		local extraArg=$extraArgMac
	else
		local generatorArg=" "
	fi

	[ ! -z "$extraArg" ] && log "Extra arguments: '$extraArg'" " -"

	# process arguments
	local argIndex=0
	local custom_config=false

	for arg in "$@" 
	do
		log "arg[$argIndex]: '$arg'"
		if [[ $argIndex -eq 0 ]]; then
			local rootDirectory=$arg
		else
			arg=$(echo $arg | tr '[:upper:]' '[:lower:]')
			[ $? -ne 0 ] && log_error "Error in tr command" " --" && return 1
			if [[ "$arg" == "only-lib" ]]; then
				log "'only-lib' option passed. Build only library without tests" " --"
				local onlyLibArg=" only-lib"
				local cmakeTestsArg=" "
			elif [[ "$arg" == "g++" ]]; then
				log "'g++' option passed. Build with g++ compiler" " --"
				local cmakeGppArg= -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gpp
				local gppArg="g++"
				local buildFolderPrefix="Build-g++"
			elif [[ "$arg" == "no-log" ]]; then
				log "'no-log' option passed. Turn off LOG_ON compile definition" " --"
				local logArg=" "
			elif [[ "$arg" == "release" ]]; then
				log "'release' option passed. Set Release build type" " --"
				local buildConfig="Release"
				if [ -f "$THIS_DIR/build_config_release.sh" ]; then
					log "Load build_config_release.sh"
					source $THIS_DIR/build_config_release.sh
					local custom_config=true
				else
					log "build_config_release.sh was not found. You can create it and override settings for release build"
				fi
			elif [[ "$arg" == "configure" ]] || [[ "$arg" == "-c" ]]; then
				log "'$arg' option passed. Will not build the project. Only make the config" " --"
				local onlyConfig=true
			elif [[ "$arg" == "reconfigure" ]] || [[ "$arg" == "-rc" ]]; then
				log "'$arg' option passed. Will not build the project. Only make the config and remove CMakeCache.txt" " --"
				local onlyConfig=true
				local reconfigure=true
			elif [[ "$arg" == "reconfigure" ]] || [[ "$arg" == "-rcb" ]]; then
				log "'$arg' option passed. Will reconfigure and build the project." " --"
				local reconfigure=true
			fi
		fi	
		local argIndex=$((argIndex + 1))
	done

	if ! $custom_config; then
		log "Load build_config.sh"
		source $THIS_DIR/build_config.sh
	fi

	# check for dependencies
	local enterDirectory=${PWD}
	if [ -f "$THIS_DIR/get_dependencies.sh" ]; then
		source $THIS_DIR/get_dependencies.sh $@
		local retval=$?
		if [ $retval -ne 0 ]; then
			log_error "Dependencies resolution error" " --"
			return 1
		else
			log_success "Done with dependencies" " --"
			cd "$enterDirectory"
		fi
	fi

	[ ! -d "$rootDirectory" ] && log_error "Non-existent project directory passed '$rootDirectory'" " -" && return 5

	if [[ "$rootDirectory" != "." ]]; then
		local folderName=$rootDirectory
	fi

	local configure_cmd="cmake ..$generatorArg$logArg$extraArg"
	local build_cmd="cmake --build . --config=$buildConfig"
	local build="$rootDirectory/${buildFolderPrefix}-cmake"

	if [ -f "$THIS_DIR/pre_build.sh" ]; then
		$THIS_DIR/pre_build.sh $@
		[ $? -ne 0 ] && log_error "pre_build.sh error" " -" && return 6
	fi

	if [ -f "$rootDirectory/pre_build.sh" ]; then
		source $rootDirectory/pre_build.sh $@
		[ $? -ne 0 ] && log_error "$rootDirectory/pre_build.sh error" " -" && return 7
	fi

	log "Output directory: '$build'" " -"

	[ ! -d "$build" ] && mkdir $build || log "	already exists" " --"
	cd "$build"

	if $reconfigure; then
		local cmd="rm CMakeCache.txt"
		log "Remove CMakeCache.txt cmd: '$cmd'"
		$cmd
	fi
	log "Configure with CMake command: '$configure_cmd'" "\033[0;36m" "\033[0m"
	$configure_cmd

	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "CMake configure error" " -"
		cd "$enterDirectory"
		return 2
	else
		log_success "CMake configuring has been successfully done" " -"
	fi

	[ "$onlyConfig" == true ] && log "Exit without build" " -" && return 4 || log "Run cmake --build" " -"

	log "$build_cmd" "\033[0;36m" "\033[0m"
	$build_cmd

	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "CMake build error" " -"
		cd "$enterDirectory"
		return 3
	else
		log_success "CMake building is successfully done" "-" " ---"
	fi

	cd "$enterDirectory"

	log_success "Finished build" " -" " ---"
}

build $@