#!/bin/bash

FILE_UTILS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source $FILE_UTILS_DIR/os.sh

function file_insert_before() {
	[ -z "$1" ] && return -10 # file name
	[ -z "$2" ] && return -20 # string before which to insert
	[ -z "$3" ] && return -30 # what to insert
	#sed -i "" "s/$2/$3$2/" "$1"
	# Use python due to platform independence
	# use relative paths due to platform independence
	local fpath=$(realpath --relative-to="$(to_win_path "${PWD}")" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local file_py_path=$(system_path "$THIS_DIR/file_utils.py")
	local ret=$(python $file_py_path insert_before "$fpath" "$2" "$3")
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
	# Use python due to platform independence
	# use relative paths due to platform independence
	local current_path="${PWD}"
	local fpath=$(realpath --relative-to="$current_path" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local file_path_for_python=$(system_path "$fpath")
	local file_py_path=$(system_path "$THIS_DIR/file_utils.py")
	local ret=$(python $file_py_path replace "$file_path_for_python" "$2" "$3")
	local res=$?
	echo "$ret"
	return $res
}

# Usage:
# if [ $(file_search "$root_dir/.gitignore" "$key") -ne -1 ]; then
# 	echo "Found"
# else
# 	echo "Not found"
# fi
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
	fpath=$(realpath --relative-to="$(to_win_path "${PWD}")" "$1")
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	local file_py_path=$(system_path "$THIS_DIR/file_utils.py")
	local ret=$(python $file_py_path search "$fpath" "$2" "$3")
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
	cd "$1"
	[ $? -ne 0 ] && return 2
	echo $(pwd)
}

function dir_name() {
	[ -z "$1" ] && return 1 # directory path
	[ ! -d "$1" ] && return 2
	echo $(basename "$(dirname "$1")")
}

function file_full_path() {
	[ -z "$1" ] && return 1 # file path
	local file_name=$(basename "$1")
	local dir_name=$(dirname "$1")
	cd $dir_name
	[ $? -ne 0 ] && return 2
	echo "$(pwd)/$file_name"
}

function normalize_path() {
	local path="$1"
	# Check if the path is just a file name
	if [[ ! "$path" =~ / ]]; then
		# Get the absolute path of the current directory and append the file name
		echo "$(pwd -P)/$path"
	else
		# Normalize the path using cd and pwd
		echo "$(cd "$(dirname "$path")" && cd "$(basename "$path")" && pwd -P)"
	fi
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

function to_win_path() {
	if is_win_path "$1"; then
		echo "$1"
	else
		if command -v wslpath > /dev/null 2>&1; then
			echo $(wslpath -w "$1")
		elif command -v cygpath > /dev/null 2>&1; then
			echo $(cygpath -w "$1")
		else
			echo "$1"
		fi
	fi
}

function bash_path() {
	if is_wsl; then
		echo $(wslpath -u "$1")
	elif is_cygwin; then
		echo $(cygpath -u "$1")
	else
		# Letter should be converted to lower case
		echo $(echo "$1" | sed -e 's/\\/\//g' -e 's/^\([a-zA-Z]\):/\/\L\1/')
	fi
}

function to_nix_path() {
	if is_win_path "$1"; then
		if is_wsl_path "$1"; then
			echo $(wslpath -u "$1")
		elif is_cygpath "$1"; then
			echo $(cygpath -u "$1")
		else
			echo $(bash_path "$1")
		fi
	else
		echo "$1"
	fi
}

function is_win_path() {
	local path="$1"
	# Check if the path matches the Windows format (e.g., C:\ or D:\)
	if [[ "$path" =~ ^[a-zA-Z]:\\ ]]; then
		true
	else
		false
	fi
}

function is_wsl_path() {
	local path="$1"
	# Check if the path matches the WSL format (e.g., /mnt/c/ or /c/)
	if [[ "$path" =~ ^/mnt/[a-zA-Z]/ ]]; then
		true
	else
		false
	fi
}

function is_cygpath() {
	local path="$1"
	# Check if the path matches the Cygpath format (e.g., /cygdrive/c/ or /cygdrive/d/)
	if [[ "$path" =~ ^/cygdrive/[a-zA-Z]/ || "$path" =~ ^/[a-zA-Z]/ ]]; then
		true
	else
		false
	fi
}

function system_path() {
	if is_windows; then
		to_win_path "$1"
	else
		to_nix_path "$1"
	fi
}

function directory_tree() {
	find $1 | sed -e "s/[^-][^\/]*\// |/g" -e "s/|\([^ ]\)/|-\1/"
}

function symlink() {
	[ -z "$1" ] && echo "No source file provided" && return 1 || local src="$1"
	[ -z "$2" ] && echo "No destination file provided" && return 2 || local dest="$2"
	local fname=$(basename "$src")
	if [ -d $dest ]; then
		local dest_complete_path="$dest/$fname"
	elif [ -f $dest ]; then
		local dest_complete_path="$dest"
	fi
	[ -L "$dest_complete_path" ] && echo "Destination file is already a symlink: '$dest_complete_path'" && return 3
	[ -f "$dest_complete_path" ] && echo "Destination file already exists: '$dest_complete_path'" && return 4
	[ -d "$dest_complete_path" ] && echo "Destination directory already exists: '$dest_complete_path'" && return 5
	local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
	source $THIS_DIR/os.sh
	[ $? -ne 0 ] && echo "Failed to include os.sh" && return 6
	if is_windows; then
		# Call symlink command trhough file_utils.bat
		local THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
		# if is full path:
		local full_path_src=$(full_path "$src")
		[ $? -ne 0 ] && echo "Failed to get full path of the source" && return 7
		mkdir -p "$dest"
		[ $? -ne 0 ] && echo "Failed to create the destination directory" && return 8
		local full_path_dest=$(file_full_path "$dest")
		local win_path_src=$(cygpath -w $full_path_src)
		local win_path_dest=$(cygpath -w $full_path_dest)
		$THIS_DIR/file_utils.bat symlink "$win_path_src" "$win_path_dest"
	else
		ln -s "$src" "$dest"
	fi
	local code=$?
	[ $code -ne 0 ] && echo "Failed to create the symlink. Error code: $code" && return 7
}
