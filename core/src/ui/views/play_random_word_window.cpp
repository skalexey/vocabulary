#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/label.h>
#include <abstract_ui/widgets/text.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/play_random_word_window.h"

namespace vocabulary_core
{
	play_random_word_window::play_random_word_window()
		: base()
	{
		construct();
	}
	
	play_random_word_window::play_random_word_window(const utils::ui::dialog_ptr& impl)
		: base(impl)
	{
		construct();
	}

	void play_random_word_window::construct()
	{
		do_on_post_construct([self = this]() {
			return self->this_on_post_construct();
		});
	}

	int play_random_word_window::this_on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::type::automatic, size_policy::type::automatic);
		// Not every implementation support automatic resize properly
		set_size({ 500, 700 });
		set_modal(false);
		set_title("Random Word Game");
		m_show_example_button = create<button>();
		m_show_example_button->set_text("Show Example");
		m_show_translation_button = create<button>();
		m_show_translation_button->set_text("Show Translation");
		m_i_know_it_button = create<button>();
		m_i_know_it_button->set_text("I Know It");
		m_skip_button = create<button>();
		m_skip_button->set_text("Skip");
		m_word_label = create<label>();
		m_example_label = create<text>();
		m_translation_label = create<text>();
		// Center dialog on the second half of the screen
		add_on_update([self = this](float dt) {
			auto screen_size = self->get_screen_size();
			auto size = self->get_size();
			if (screen_size.x > screen_size.y)
				self->set_position({(screen_size.x / 2 - size.x) / 2 + screen_size.x / 2, screen_size.y / 2 - size.y / 2});
			else
				self->set_position({screen_size.x / 2 - size.x / 2, (screen_size.y / 2 - size.y) / 2 + screen_size.y / 2});
			return true;
		});
		return 0;
	}
}