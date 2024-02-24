#include <cmath>
#include <random>
#include <algorithm>
#include <utils/Log.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/text_input.h>
#include <abstract_ui/app.h>
#include "app.h"
#include "words.h"
#include "word.h"
#include "ui/controllers/new_word_controller.h"
LOG_TITLE("new_word_controller");

extern words g_words;

namespace vocabulary_core
{
	int new_word_controller::on_post_construct()
	{
		set_view<vocabulary_core::new_word_window>();
		view().store_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("store_button clicked");
			auto& word_value = self->view().word_input().get_value();
			auto add_word_result = g_words.new_word(word_value);
			auto store_word = [=] (word& w) {
				w.set_example(self->view().example_input().get_value());
				w.set_translation(self->view().translation_input().get_value());
				self->view().word_input().set_value("");
				self->view().example_input().set_value("");
				self->view().translation_input().set_value("");
				if (g_words.update_local_storage() == 0)
					self->app().show_message("Word stored successfully");
				else
					self->app().show_message("Failed to store the word");
			};
			if (add_word_result.second == 0)
				store_word(add_word_result.first);
			else
				if (add_word_result.second == words::word_exists)
					self->app().ask_user("Word already exists. Do you want to update it?", [=](bool yes) {
						if (yes)
							store_word(add_word_result.first);
					});
		});
		view().store_button().set_enable_if([self = this]() {
			return !self->view().word_input().get_value().empty() && (!self->view().example_input().get_value().empty() || !self->view().translation_input().get_value().empty());
		});
		return 0;
	}

	vocabulary_core::app& new_word_controller::app()
	{
		return dynamic_cast<vocabulary_core::app&>(base::app());
	}

	const vocabulary_core::app& new_word_controller::get_app() const
	{
		return dynamic_cast<const vocabulary_core::app&>(base::get_app());
	}
}
