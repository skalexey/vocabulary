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

    source $THIS_DIR/../deps_config.sh
    source $THIS_DIR/../dependencies.sh

    # ImGui
    # 5a2b1e84828f192d30c91cdd210db41de8ad3236 - before January 28
    # 96839b445e32e46d87a44fd43a9cdd60c806f7e1 - after January 28
    download_dependency "imgui" "$depsLocation" "https://github.com/ocornut/imgui.git"
    # SDL
    download_dependency "SDL" "$depsLocation" "https://github.com/libsdl-org/SDL.git"

    if [ ! -f "$THIS_DIR/main_sdl_imgui.cpp" ]; then
        cp "$depsLocation/imgui/examples/example_sdl_sdlrenderer/main.cpp" "main_sdl_imgui.cpp"
    fi

    source $depsLocation/abstract_ui/sdl_imgui/deps_scenario.sh
    retcode=$?
    [ $retcode -ne 0 ] && log_error "Error occured during the sdl_imgui deps_scenario.sh execution: $retcode " " -" && return $retcode
    return 0
}

deps_scenario $@
