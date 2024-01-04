#!/bin/bash

function git_clone()
{
	git clone $1
	local retval=$?
	[[ $? -ne 0 ]] && return 1 || return 0
}

function check_download_type()
{
	[[ $2 =~ .*$1* ]] && true && return 0
	[[ $3 =~ .*$1* ]] && true || false
}

function direct_download()
{
	[ -z "$2" ] && local o="dwl" || local o="$2"
	wget $1 -O "$o"
	[ $? -ne 0 ] && curl -L $1 -o "$o"
	erc=$?
	[ $erc -ne 0 ] && echo "Download error: $erc" && return 1

	if check_download_type "tar.bz" $@ || check_download_type "tar.gz" $@; then
		tar -xvf "$o"
		[ $? -ne 0 ] && echo "Tar bz extraction error" && return 2
		rm "$o"
		return $?
	else
		return 3 # Unknown file type
	fi
	return 0
}

function download()
{
	if [[ $1 =~ .*\.git ]]; then
		git_clone $@
	else
		direct_download $@
	fi
	return $?
}
