#!/usr/bin/bash

function log()
{
	[ -z "$1" ] && exit 0
	[ ! -z "$2" ] && local local_prefix="$2$log_prefix" || local local_prefix="$log_prefix"
	[ ! -z "$3" ] && local local_postfix="$log_postfix$3" || local local_postfix="$log_postfix"
	echo -e "$local_prefix$1$local_postfix"
}

function log_error()
{
	log "$1" "\033[0;31m$2" "$3\033[0m"
}

function log_warning()
{
	log "$1" "\033[0;33m$2" "$3\033[0m"
}

function log_success()
{
	log "$1" "\033[0;32m$2" "$3\033[0m"
}

function log_info()
{
	log "$1" "\033[0;36m$2" "$3\033[0m"
}

logsh_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
[ -f $logsh_dir/string_utils.sh ] && source $logsh_dir/string_utils.sh

function log_into_file()
{
	[ -z "$1" ] && exit 0
	[ ! -z "$2" ] && local log_file=$2 || local log_file="$(fname_date_and_time).txt"
	echo -e "$1" >> $log_file
}

function log_into_file_and_print()
{
	log_into_file "$1"
	log "$1"
}