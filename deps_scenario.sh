#!/bin/bash

function deps_scenario()
{
    local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    local log_prefix="-- [$(basename $THIS_DIR) $(basename "${BASH_SOURCE[0]}")]: "
    log_info "Start deps_scenario" " -"
	
    source $THIS_DIR/dependencies.sh
    source $THIS_DIR/deps_config.sh

    source "$depsLocation/DataModelBuilder/Core/deps_scenario.sh"
    download_dependency "DataModelBuilder" "$depsLocation" "git@github.com:skalexey/DataModelBuilder.git"
    download_dependency "Networking" "$depsLocation" "git@github.com:skalexey/Networking.git"
    source "$depsLocation/Networking/deps_scenario.sh"
    download_dependency "lua-5.4.4" "$depsLocation" "http://www.lua.org/ftp/lua-5.4.4.tar.gz"
    download_dependency "boost_1_81_0" "$depsLocation" "https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.bz2"
    download_dependency "abstract_ui" "$depsLocation" "git@github.com:skalexey/abstract_ui.git"
}

deps_scenario $@
