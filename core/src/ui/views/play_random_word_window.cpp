#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/label.h>
#include <abstract_ui/widgets/text.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/play_random_word_window.h"

namespace vocabulary_core
{
	play_random_word_window::play_random_word_window(const utils::ui::dialog_ptr& impl)
		: base(impl)
	{
		// set_auto_resize(true);
		set_size({ 500, 700 });
		set_title("Random Word Game");
		set_on_show([this]() {
			m_word_label->show();
			m_example_label->show();
			m_translation_label->show();
			m_show_example_button->show();
			m_show_translation_button->show();
			m_i_know_it_button->show();
			m_skip_button->show();
		});
		do_on_post_construct([self = this]() {
			return self->this_on_post_construct();
		});
	}

	int play_random_word_window::this_on_post_construct()
	{
		using namespace utils::ui;
		m_show_example_button = create<button>();
		m_show_example_button->set_text("show Example");
		m_show_translation_button = create<button>();
		m_show_translation_button->set_text("show Translation");
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