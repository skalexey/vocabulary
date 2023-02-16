#!/bin/bash

function pull_php_includes() {
	source serverside_config.sh
	source log.sh
	local log_prefix="[pull_php_includes]: "
	log_info "Pull php includes"
	
	ssh $ssh_user@$ssh_host << HERE
		echo "domain_dir: $domain_dir"
		[ -z "$domain_dir" ] && echo "No data captured. Exit" && exit 1
		if [ ! -d "$domain_dir" ]; then
			echo "There is no domain directory '$domain_dir'" && exit 1
		fi
		cd "$domain_dir"
		if [ ! -d "php_utils" ]; then
			git clone https://github.com/skalexey/php_utils.git
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