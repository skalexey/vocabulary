
#pragma once

#include <deque>
#include <string>
#include <memory>
#include "ui/controllers/view_controller.h"
#include "ui/views/play_random_word_window.h"

class word;

namespace vocabulary_core
{
	class play_random_word_controller : public vocabulary_core::view_controller
	{
		using base = utils::ui::view_controller;

	public:
		play_random_word_window& view() {
			return dynamic_cast<play_random_word_window&>(base::view());
		}
		void show_random_word();

	protected:
		word& current_word();
		int on_post_construct() override;

	private:
		std::deque<std::string> m_words_queue;
		std::string m_current_word;
		bool m_example_shown = false;
		bool m_translation_shown = false;
	};
	using play_random_word_controller_ptr = std::shared_ptr<play_random_word_controller>;
}
