#pragma once

#include <memory>
#include <stdio.h>
#include <csignal>
#include <SDL3/SDL.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/io_utils.h>
#include <utils/print_defs.h>
#include <utils/common.h>
#include <utils/log.h>
#include "ImGui-SDL/include/app.h"

LOG_TITLE("app");

using utils::void_int_cb;

namespace
{
	const std::string log_fname = "vocabulary_log.txt";
}

app::app(int argc, char* argv[])
	: utils::ui::app(argc, argv)
	, vocabulary_core::app(argc, argv)
	, utils::ui::imgui::sdl_app(argc, argv)
{
	// Default resolution
	set_resolution(1280, 720);
	set_clear_color({0.05f, 0.05f, 0.07f, 1.00f});
	// Create a new log file
	std::ofstream f(utils::file::temp_directory_path() / log_fname);
}

int app::init()
{
	return vocabulary_core::app::init();
}

SDL_Window* app::create_window()
{
	auto& r = get_resolution();
	Uint32 window_flags = (Uint32)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
	return SDL_CreateWindow("Vocabulary", r.x, r.y, window_flags);
}

bool app::on_update(float dt) {
	if (!m_log_stream.str().empty())
		m_log_stream.out();
	return true;
}

void app::log_stringstream::out()
{
	if (str().empty())
		return;
	std::ofstream f(utils::file::temp_directory_path() / log_fname, std::ios::app);
	assert(f.is_open());
	f << str();
	SDL_Log("%s", str().c_str());
	str("");
}