#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/label.h>
#include <abstract_ui/widgets/text.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/play_random_word_window.h"

namespace vocabulary_core
{
	int play_random_word_window::on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::type::automatic, size_policy::type::automatic);
		// Not every implementation supports automatic resize properly
		set_size({ 500, 700 });
		set_modal(false);
		set_title("Random Word Game");
		set_max_width(250);
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
		return 0;
	}
}