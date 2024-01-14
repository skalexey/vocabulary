#!/bin/bash

function pre_build()
{
	local folderName=${PWD##*/}
	source log.sh
	local log_prefix="-- [${folderName} pre_build.sh]: "
	log_info "Pre-configuration"
	configure_cmd="cmake ..$generatorArg$logArg$extraArg -DCMAKE_BUILD_TYPE=$buildConfig"
	build_cmd="cmake --build ."
	build="$build-$buildConfig"
}

pre_build $@