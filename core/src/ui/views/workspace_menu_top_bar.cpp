#include <abstract_ui/app.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/workspace_menu_top_bar.h"
#include <utils/Log.h>
LOG_TITLE("vocabulary_core::workspace_menu_top_bar");

namespace vocabulary_core
{
	int workspace_menu_top_bar::on_post_construct()
	{
		using namespace utils::ui;
		//set_title("Workspace Menu Top Bar");
		m_actions_button = create<button>();
		m_actions_button->set_text("Actions");
		m_settings_button = create<button>();
		m_settings_button->set_text("Settings");
		return 0;
	}
}