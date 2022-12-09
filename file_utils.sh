#!/bin/bash

function file_insert_before() {
	[ -z "$1" ] && return 1 # file name
	[ -z "$2" ] && return 2 # string before which to insert
	[ -z "$3" ] && return 3 # what to insert
	#sed -i "" "s/$2/$3$2/" "$1"
	# Use python due to platform independence
	# use relative paths due to platform independence
	fpath=$(realpath --relative-to="${PWD}" "$1")
	return $(python -c "from file_utils import*; insert_before(\"$fpath\", \"$2\", \"$3\");")
}

function file_append_line() {
	[ -z "$1" ] && return 1 # file name
	[ -z "$2" ] && return 2 # string to append at the end of the file
	echo "$2" >> "$1"
}

function file_replace() {
	[ -z "$1" ] && return 1 # file name
	[ -z "$2" ] && return 2 # regex to find
	[ -z "$3" ] && return 3 # text to replace regex to
	#echo "s/$2/$3/g$4"
	sed -i.bac -E "s/$2/$3/g$4" $1
	[ -f "$1.bac" ] && rm $1.bac
	# Use python due to platform independence
	# use relative paths due to platform independence
	# fpath=$(realpath --relative-to="${PWD}" "$1")
	# return $(python -c "from file_utils import*; replace(\"$fpath\", \"$2\", \"$3\");")
}

function file_search() {
	[ -z "$1" ] && return 1 # file name
	[ -z "$2" ] && return 2 # regex to find

	#echo "in $1 find $2"
	local contents=$(<$1)
	local nl=$'\n'
	local rest=${contents#*$2}
	local res=$(( ${#contents} - ${#rest} - ${#2} ))
	[ $res -ge 0 ] && echo $res || echo "-1"
	#[[ $(cat $1) =~ .*$2* ]] && true || false
}

function file_regex() {
	echo $(python -c "from file_utils import*; print(search(\"$1\", \"$2\", \"$3\"));")
}

function full_path() {
	[ -z "$1" ] && return 1 # input path
	[ -d "$1" ] && dir_full_path $1
	[ -f "$1" ] && file_full_path $1
}

function dir_full_path() {
	[ -z "$1" ] && return 1 # directory path
	[ ! -d "$1" ] && return 2
	
	local cur_dir="${PWD}"
	cd "$1"
	echo ${PWD}
	cd "$cur_dir"
}

function dir_name() {
	[ -z "$1" ] && return 1 # directory path
	[ ! -d "$1" ] && return 2
	
	local dp="$(dir_full_path "$1")"
	echo $(basename "$dp")
}

function file_full_path() {
	[ -z "$1" ] && return 1 # file path
	[ ! -f "$1" ] && return 2
	
	local file_dir=$(dirname "$1")
	local file_name=$(basename "$1")
	local cur_dir="${PWD}"
	cd "$file_dir"
	echo ${PWD}/$file_name
	cd "$cur_dir"
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
