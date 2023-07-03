#include <utils/ui/app.h>
#include <utils/ui/widgets/dialog.h>
#include <utils/ui/widgets/button.h>
#include <utils/ui/widgets/label.h>
#include <utils/ui/widgets/text.h>
#include <utils/ui/widget_factory.h>
#include "ui/views/play_random_word_window.h"

namespace vocabulary_core
{
	play_random_word_window::play_random_word_window()
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
		m_show_example_button = get_factory().create<button>(this);
		m_show_example_button->set_text("show Example");
		m_show_translation_button = get_factory().create<button>(this);
		m_show_translation_button->set_text("show Translation");
		m_i_know_it_button = get_factory().create<button>(this);
		m_i_know_it_button->set_text("I Know It");
		m_skip_button = get_factory().create<button>(this);
		m_skip_button->set_text("Skip");
		m_word_label = get_factory().create<label>(this);
		m_example_label = get_factory().create<text>(this);
		m_translation_label = get_factory().create<text>(this);
		return 0;
	}
}