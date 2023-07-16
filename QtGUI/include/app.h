#pragma once

#include <iostream>
#include <sstream>
#include <abstract_ui/qt/app.h>
#include <core/include/app.h>

class app : public utils::ui::qt::app, public vocabulary_core::app
{
public:
	app(int argc, char* argv[]);
	bool on_update(float dt) override final;

protected:
	int init() override;

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

