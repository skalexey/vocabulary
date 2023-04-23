#!/bin/bash

is_windows() {
	if [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
		true
	else
		false
	fi
}

is_nix() {
	! is_windows
}

is_mac() {
	[[ $OSTYPE =~ .*darwin* ]] && true || false
}

is_linux() {
    [[ $OSTYPE =~ .*linux* ]] && true || false
}
