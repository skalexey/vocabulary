#include <cmath>
#include <random>
#include <algorithm>
#include <utils/Log.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/label.h>
#include <abstract_ui/app.h>
#include "words.h"
#include "word.h"
#include "ui/controllers/play_random_word_controller.h"
LOG_TITLE("play_random_word_controller");

extern words g_words;

namespace vocabulary_core
{
	int play_random_word_controller::on_post_construct()
	{
		set_view<vocabulary_core::play_random_word_window>();
		view().show_example_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("show_example_button");
			if (self->m_current_word.empty())
				return;
			self->view().example_label().set_text(self->current_word().get_example());
			self->m_example_shown = true;
		});
		view().show_translation_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("show_translation_button");
			if (self->m_current_word.empty())
				return;
			auto& w = self->current_word();
			self->view().translation_label().set_text(!w.get_translation().empty() ? std::string(w.get_translation().begin(), w.get_translation().end()) : "no translation");
			self->m_translation_shown = true;
		});
		view().i_know_it_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("i_know_it_button");
			if (self->m_current_word.empty())
				return;
			auto& w = self->current_word();
			float example_cost = self->m_example_shown ? 0.5f : 0.0f;
			float translation_cost = self->m_translation_shown ? 1.f : 0.f;
			auto m = std::max(0.f, (1.0f - example_cost - translation_cost));
			w.set_level(char(word::level_max * m));
			g_words.update_local_storage();
			self->m_example_shown = false;
			self->m_translation_shown = false;
			self->show_random_word();
		});
		view().skip_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("skip_button");
			self->show_random_word();
		});
		show_random_word(); // Assuming the words have been loaded
		return 0;
	}

	void play_random_word_controller::show_random_word()
	{
		if (g_words.list.empty()) {
			LOG_DEBUG("show_random_word(): No words");
			return;
		}
		if (m_words_queue.empty()) {
			std::for_each(g_words.list.begin(), g_words.list.end(), [self = this](const auto& pair) {
				if (pair.second.get_level() < word::level_max)
					self->m_words_queue.push_back(pair.first);
			});
			std::shuffle(m_words_queue.begin(), m_words_queue.end(), std::random_device());
		}
		view().translation_label().set_text("");
		view().example_label().set_text("");
		if (m_words_queue.empty())
		{
			view().example_label().set_text("Congratulations!!! You know all the words!");
			return;
		}
		m_current_word = m_words_queue.back();
		view().word_label().set_text(m_current_word);
		m_words_queue.pop_back();
	}

	word& play_random_word_controller::current_word()
	{
		return g_words.list.value(m_current_word);
	}
}
