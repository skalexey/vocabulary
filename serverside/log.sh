#!/usr/bin/bash

log()
{
	[ -z "$1" ] && exit 0
	[ ! -z "$2" ] && local local_prefix="$2$log_prefix" || local local_prefix="$log_prefix"
	[ ! -z "$3" ] && local local_postfix="$log_postfix$3" || local local_postfix="$log_postfix"
	echo -e "$local_prefix$1$local_postfix"
}

log_error()
{
	log "$1" "\033[0;31m$2" "$3\033[0m"
}

log_warning()
{
	log "$1" "\033[0;33m$2" "$3\033[0m"
}

log_success()
{
	log "$1" "\033[0;32m$2" "$3\033[0m"
}

log_info()
{
	log "$1" "\033[0;36m$2" "$3\033[0m"
}
