#!/bin/bash

function ask_user() {
	[ -z "$1" ] && echo "[ask_user]: No question provided" && return 1

	local res=false

	while true; do
		read -p "$(echo $@) (y/n) " yn
		case $yn in 
			[yY] ) res=true
				break;;
			[nN] ) res=false
				break;;
			* ) echo invalid response;;
		esac
	done

	$res
}
