
#pragma once

#include <deque>
#include <string>
#include <memory>
#include <utils/ui/window_controller.h>
#include "ui/views/play_random_word_window.h"

class word;

namespace vocabulary_core
{
	class play_random_word_controller : public utils::ui::window_controller
	{
		using base = utils::ui::window_controller;

	public:
		play_random_word_controller(utils::ui::app& app);
		play_random_word_window& view() {
			return *std::dynamic_pointer_cast<play_random_word_window>(get_view());
		}
		void show_random_word();

	protected:
		word& current_word();

	private:
		std::deque<std::string> m_words_queue;
		std::string m_current_word;
		bool m_example_shown = false;
		bool m_translation_shown = false;
	};
	using play_random_word_controller_ptr = std::shared_ptr<play_random_word_controller>;
}
