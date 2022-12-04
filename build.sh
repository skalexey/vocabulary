#!/bin/bash

build()
{
	local folderName=${PWD##*/}

	source log.sh
	local log_prefix="-- [${folderName} build script]: "

	log "Build for OS: $OSTYPE" " -" " ---"

	if [ -f "deps_config.sh" ]; then
		source deps_config.sh
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
	
	source os.sh

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
		echo "arg[$argIndex]: '$arg'"
		
		if [[ $argIndex -eq 0 ]]; then
			local rootDirectory=$arg
		else
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
				if [ -f "build_config_release.sh" ]; then
					log "Load build_config_release.sh"
					source build_config_release.sh
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
		source build_config.sh
	fi

	# check for dependencies
	local enterDirectory=${PWD}
	if [ -f "get_dependencies.sh" ]; then
		source get_dependencies.sh $@
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

	local build="$rootDirectory/${buildFolderPrefix}-cmake"

	log "Output directory: '$build'" " -"

	[ ! -d "$build" ] && mkdir $build || log "	already exists" " --"
	cd "$build"

	if $reconfigure; then
		local cmd="rm CMakeCache.txt"
		log "Remove CMakeCache.txt cmd: '$cmd'"
		$cmd
	fi
	cmd="cmake ..$generatorArg$logArg$extraArg"
	log "Configure with CMake command: '$cmd'" "\033[0;36m" "\033[0m"
	$cmd

	local retval=$?
	if [ $retval -ne 0 ]; then
		log_error "CMake configure error" " -"
		cd "$enterDirectory"
		return 2
	else
		log_success "CMake configuring has been successfully done" " -"
	fi

	[ "$onlyConfig" == true ] && log "Exit without build" " -" && return 4 || log "Run cmake --build" " -"

	log "cmake --build . --config=$buildConfig" "\033[0;36m" "\033[0m"
	cmake --build . --config=$buildConfig

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