#!/bin/bash

function file_insert_before() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # string before which to insert
	[ -z "$3" ] && return -30 # what to insert
	#sed -i "" "s/$2/$3$2/" "$1"
	# Use python due to platform independence
	# use relative paths due to platform independence
	local fpath=$(realpath --relative-to="${PWD}" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local ret=$(python $THIS_DIR/file_utils.py insert_before "$fpath" "$2" "$3")
	local res=$?
	echo "$ret"
	return $res
}

function file_insert_after() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # string after which to insert
	[ -z "$3" ] && return -30 # what to insert
	file_replace "$1" "$2" "$2$3"
	return $?
}

function file_append_line() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # string to append at the end of the file
	echo "$2" >> "$1"
}

function file_replace() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # regex to find
	[ -z "$3" ] && return -30 # text to replace regex to
	# Use sed
	# sed -i.bac -E "s/$2/$3/g$4" $1
	# [ -f "$1.bac" ] && rm $1.bac
	# Use python due to platform independence
	# use relative paths due to platform independence
	local fpath=$(realpath --relative-to="${PWD}" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local ret=$(python $THIS_DIR/file_utils.py replace "$fpath" "$2" "$3")
	local res=$?
	echo "$ret"
	return $res
}

function file_search() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # regex to find

	#echo "in $1 find $2"
	local contents=$(<$1)
	local nl=$'\n'
	local rest=${contents#*$2}
	local ret=$(( ${#contents} - ${#rest} - ${#2} ))
	local res=$?
	[ $ret -ge 0 ] && echo $ret || echo "-1"
	return $res
	#[[ $(cat $1) =~ .*$2* ]] && true || false
}

function file_regex() {
	fpath=$(realpath --relative-to="${PWD}" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local ret=$(python $THIS_DIR/file_utils.py search "$fpath" "$2" "$3")
	local res=$?
	echo $ret
	return $res
}

function full_path() {
	[ -z "$1" ] && return 1 # input path
	[ -d "$1" ] && dir_full_path $1
	[ -f "$1" ] && file_full_path $1
	return $?
}

function dir_full_path() {
	[ -z "$1" ] && return 1 # directory path
	echo "$(cd "$1" && pwd)"
}

function dir_name() {
	[ -z "$1" ] && return 1 # directory path
	[ ! -d "$1" ] && return 2
	echo $(basename "$(dirname "$1")")
}

function file_full_path() {
	[ -z "$1" ] && return 1 # file path
	local file_name=$(basename "$1")
	echo "$(cd "$(dirname "$1")" && pwd)/$file_name"
}

function file_extension() {
	[ -z "$1" ] && return 1 # file path
	fname=$(basename "$1")
	echo "${fname##*.}"
}

function rename() {
	[ -z "$1" ] && echo "No path specified" && return 1 # path
	[ ! -d "$1" ] && [ ! -f "$1" ] && echo "No file or directory exists in the given path '$1'" && return 2
	[ -z "$2" ] && echo "No new name specified" && return 3 # new name
	
	local b=$(dirname "$1")
	local new_path="$b/$2"
	if [ -d "$new_path" ] || [ -f "$new_path" ]; then
		echo "This name is already taken: '$new_path'"
		return 3
	fi
	mv "$1" "$new_path"
}

function file_newer() {
	[ -z "$1" ] && echo "No file 1 provided" && return 1 || local file1="$1"
	[ -z "$2" ] && echo "No file 2 provided" && return 2 || local file2="$2"
	[ "$file2" -ot "$file1" ] && true || false
}
