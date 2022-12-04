#!/bin/bash

source os.sh

if is_mac; then
	path="vocabulary"	
else
	path="vocabulary.exe"
fi

cd Build-cmake/
./Debug/$path
