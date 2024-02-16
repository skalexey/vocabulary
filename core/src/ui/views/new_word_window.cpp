#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/text_input.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/new_word_window.h"
#include <utils/Log.h>
LOG_TITLE("vocabulary_core::new_word_window");
namespace vocabulary_core
{
	int new_word_window::on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::type::automatic, size_policy::type::automatic);
		// Not every implementation support automatic resize properly
		set_size({ 500, 700 });
		set_modal(false);
		set_title("New word");
		m_word_input = create<text_input>();
		m_word_input->set_label("Word");
		m_example_input = create<text_input>();
		m_example_input->set_label("Example");
		m_translation_input = create<text_input>();
		m_translation_input->set_label("Translation");
		m_store_button = create<button>();
		m_store_button->set_text("Store");
		// Center dialog on the first half of the screen
		add_on_update([self = this](float dt) {
			auto screen_size = self->get_screen_size();
			auto size = self->get_size();
			if (screen_size.x > screen_size.y)
				self->set_position({(screen_size.x / 2 - size.x) / 2, screen_size.y / 2 - size.y / 2});
			else
				self->set_position({screen_size.x / 2 - size.x / 2, (screen_size.y / 2 - size.y) / 2});
			return true;
		});
		
		return 0;
	}
}