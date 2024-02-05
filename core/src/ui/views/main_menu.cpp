#include <abstract_ui/app.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/main_menu.h"
#include <utils/Log.h>
LOG_TITLE("vocabulary_core::main_menu");

namespace vocabulary_core
{
	main_menu::main_menu()
		: base()
	{
		construct();
	}

	main_menu::main_menu(const utils::ui::menu_ptr& impl)
		: base(impl)
	{
		construct();
	}

	void main_menu::construct()
	{
		do_on_post_construct([self = this]() {
			return self->this_on_post_construct();
		});
	}

	int main_menu::this_on_post_construct()
	{
		using namespace utils::ui;
		set_title("Main Menu");
		m_settings_button = create<button>();
		m_settings_button->set_text("Settings");
		m_new_word_button = create<button>();
		m_new_word_button->set_text("New Word");
		m_play_random_word_button = create<button>();
		m_play_random_word_button->set_text("Play Random Word");
		m_add_word_button = create<button>();
		m_add_word_button->set_text("Add Word");
		m_library_button = create<button>();
		m_library_button->set_text("Library");
		return 0;
	}
}