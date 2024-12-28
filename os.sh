#!/bin/bash

is_windows() {
	[[ is_cygwin || is_msys || is_wsl || "$OSTYPE" == "win32" ]]
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

is_wsl() {
	if grep -qi microsoft /proc/version || [ -n "$WSL_DISTRO_NAME" ] || [ -d /mnt/c ]; then
		true
	else
		false
	fi
}

is_cygwin() {
	[[ "$OSTYPE" == "cygwin" ]] && true || false
}

is_msys() {
	[[ "$OSTYPE" == "msys" ]] && true || false
}
