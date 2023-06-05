#pragma once

#include <iostream>
#include <sstream>
#include <utils/ui/imgui/sdl_app.h>
#include <core/include/app.h>

class app : public utils::ui::imgui::sdl_app, public vocabulary_core::app
{
public:
	app(int argc, char* argv[]);
	bool on_update(float dt) override;

protected:
	int init() override;

protected:
	SDL_Window* create_window() override;

private:
	class log_stringstream : public std::ostringstream
	{
		public:
			log_stringstream() = default;
			void redirect() {
				m_original_rdbuf = std::cout.rdbuf();
				std::cout.rdbuf(rdbuf());
			}
			void out();
			~log_stringstream() {
				out();
				std::cout.rdbuf(m_original_rdbuf);
			}
		private:
			std::basic_streambuf<char, std::char_traits<char>> * m_original_rdbuf = nullptr;
	};
	log_stringstream m_log_stream;
};

