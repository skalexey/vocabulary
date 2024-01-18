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
	new_word_window::new_word_window()
		: base()
	{
		construct();
	}

	new_word_window::new_word_window(const utils::ui::dialog_ptr& impl)
		: base(impl)
	{
		construct();
	}

	void new_word_window::construct()
	{
		do_on_post_construct([self = this]() {
			return self->this_on_post_construct();
		});
	}

	int new_word_window::this_on_post_construct()
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
		// Center dialog manually on first 2 frames while we are temporarily using dragging
		app().add_on_update([self = this](float dt) {
			static int cnt = 0;
			self->set_position_relative({ 0.5f, 0.5f }, { 0.5f, 0.5f });
			return cnt++ < 1;
		});
		
		return 0;
	}
}