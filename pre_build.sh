#!/bin/bash

function pre_build()
{
	local imgui_SDL_folder="ImGui-SDL"
	local qt_gui_folder="QtGUI"
	./update_cmake_modules.sh ./core
	local passedFolder=$(basename $1)
	[ "$passedFolder" == "$imgui_SDL_folder" ] && ./update_cmake_modules.sh ./ImGui-SDL || echo 0 > /dev/null
	[ "$passedFolder" == "$qt_gui_folder" ] && ./update_cmake_modules.sh ./QtGUI || echo 0 > /dev/null
}

pre_build $@