#!/bin/bash

function deps_scenario()
{
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    source $THIS_DIR/dependencies.sh
    source $THIS_DIR/deps_config.sh

    source "$depsLocation/DataModelBuilder/Core/deps_scenario.sh"
    download_dependency "DataModelBuilder" "$depsLocation" "git@github.com:skalexey/DataModelBuilder.git"
    download_dependency "Networking" "$depsLocation" "git@github.com:skalexey/Networking.git"
    source "$depsLocation/Networking/deps_scenario.sh"
    download_dependency "lua-5.4.4" "$depsLocation" "http://www.lua.org/ftp/lua-5.4.4.tar.gz"
    download_dependency "imgui" "$depsLocation" "https://github.com/ocornut/imgui.git"
    download_dependency "SDL" "$depsLocation" "https://github.com/libsdl-org/SDL.git"

    if [ ! -f "main_sdl_imgui.cpp" ]; then
        cp "$depsLocation/imgui/examples/example_sdl_sdlrenderer/main.cpp" "main_sdl_imgui.cpp"
    fi
}

deps_scenario $@
