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
}

deps_scenario $@
