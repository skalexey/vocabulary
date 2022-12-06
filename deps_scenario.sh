#!/bin/bash

function deps_scenario()
{
    source dependencies.sh
    source deps_config.sh

    download_dependency "VL" "$depsLocation" "git@github.com:skalexey/VL.git"
    download_dependency "lua-5.4.4" "$depsLocation" "http://www.lua.org/ftp/lua-5.4.4.tar.gz"
    download_dependency "imgui" "$depsLocation" "https://github.com/ocornut/imgui.git"
    download_dependency "SDL" "$depsLocation" "https://github.com/libsdl-org/SDL.git"

    if [ ! -f "main_sdl_imgui.cpp" ]; then
        cp "$depsLocation/imgui/examples/example_sdl_sdlrenderer/main.cpp" "main_sdl_imgui.cpp"
    fi
}

deps_scenario $@
