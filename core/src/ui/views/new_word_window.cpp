#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/text_input.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/new_word_window.h"

namespace vocabulary_core
{
	new_word_window::new_word_window(const utils::ui::dialog_ptr& impl)
		: base(impl)
	{
		// set_auto_resize(true);
		set_size({ 500, 700 });
		set_title("New word");
		do_on_post_construct([self = this]() {
			return self->this_on_post_construct();
		});
	}

	int new_word_window::this_on_post_construct()
	{
		using namespace utils::ui;
		m_word_input = create<text_input>();
		m_word_input->set_label("word");
		m_example_input = create<text_input>();
		m_example_input->set_label("example");
		m_translation_input = create<text_input>();
		m_translation_input->set_label("translation");
		m_store_button = create<button>();
		m_store_button->set_text("Store");
		return 0;
	}
}