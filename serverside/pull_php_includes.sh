#!/bin/bash

function pull_php_includes() {
	source serverside_config.sh
	source log.sh
	local log_prefix="[pull_php_includes]: "
	log_info "Pull php includes"
	
	ssh $ssh_user@$ssh_host << HERE
		echo "remote_dir: $remote_dir"
		[ -z "$remote_dir" ] && echo "No data captured. Exit" && exit 1
		if [ ! -d "$remote_dir" ]; then
			echo "Directory '$remote_dir' does not exist. Let's create it."
			mkdir "$remote_dir"
			[ $? -ne 0 ] && echo "Error while creating the directory '$remote_dir'" && exit 1
		fi
		cd "$remote_dir"
		if [ ! -d "include" ]; then
			git clone https://github.com/skalexey/php_utils.git
			mv php_utils/include include
			ln -s php_utils/include include
			[ ! -d "include" ] && echo "Error while cloning the repo" && exit 1
		else
			echo "Pull php_utils repo"
			[ -z "$ssh_host" ] && echo "No data captured. Exit" && exit 1
			echo "ssh_host: $ssh_host"
			cd php_utils
			git pull
			cd ..
			echo "Finished"
		fi
HERE
}

pull_php_includes $@