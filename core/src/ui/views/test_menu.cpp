#include <abstract_ui/app.h>
#include <abstract_ui/widgets/layouts/vertical_layout.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/menu_bar.h>
#include "ui/views/test_menu.h"
#include <utils/log.h>
LOG_TITLE("vocabulary_core::test_menu");

namespace vocabulary_core
{
	int test_menu::on_post_construct()
	{
		using namespace utils::ui;
		set_title("Test Menu");
		auto menu_bar = create<utils::ui::menu_bar>(&app());
		menu_bar->add_item("Test button", [self = this]() {
			LOG_DEBUG("Test button clicked");
		});
		// m_layout = create<vertical_layout>();
		// m_settings_button = create<button>(m_layout.get());
		// m_settings_button->set_text("Settings");
		// m_new_word_button = create<button>(m_layout.get());
		// m_new_word_button->set_text("New Word");
		// m_play_random_word_button = create<button>(m_layout.get());
		// m_play_random_word_button->set_text("Play Random Word");
		// m_library_button = create<button>(m_layout.get());
		// m_library_button->set_text("Library");
		return 0;
	}
}