#!/bin/bash

function deps_scenario()
{
    source dependencies.sh
    source deps_config.sh

    download_dependency "VL" "$depsLocation" "git@github.com:skalexey/VL.git"
    download_dependency "lua-5.4.4" "$depsLocation" "http://www.lua.org/ftp/lua-5.4.4.tar.gz"
}

deps_scenario $@
