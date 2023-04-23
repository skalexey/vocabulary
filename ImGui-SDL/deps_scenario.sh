#!/bin/bash

function deps_scenario()
{
    local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    local log_prefix="-- [${BASH_SOURCE[0]}]: "
    log_info "Start deps_scenario" " -"
    log "Call parent deps_scenario.sh" " -"
    source $THIS_DIR/../deps_scenario.sh
    [ $? -ne 0 ] && log_error "Error occured during the parent deps_scenario.sh execution " " -" && return 1
    log_success "Parent deps_scenario.sh work done" " -"

    source $THIS_DIR/deps_config.sh
    source $THIS_DIR/../dependencies.sh

    download_dependency "imgui" "$depsLocation" "https://github.com/ocornut/imgui.git"
    download_dependency "SDL" "$depsLocation" "https://github.com/libsdl-org/SDL.git"

    if [ ! -f "$THIS_DIR/main_sdl_imgui.cpp" ]; then
        cp "$depsLocation/imgui/examples/example_sdl_sdlrenderer/main.cpp" "main_sdl_imgui.cpp"
    fi
}

deps_scenario $@
