#!/bin/bash

function pre_build()
{
	./update_cmake_modules.sh ./core
	./update_cmake_modules.sh ./ImGui-SDL
}

pre_build $@