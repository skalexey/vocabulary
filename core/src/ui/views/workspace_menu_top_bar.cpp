#include <VL.h>
#include <abstract_ui/app.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/menu_list.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/layouts/horizontal_layout.h>
#include <abstract_ui/menu_manager.h>
#include <utils/Log.h>
#include "ui/controllers/workspace_menu_controller.h"
#include "ui/views/workspace_menu_top_bar.h"
LOG_TITLE("vocabulary_core::workspace_menu_top_bar");

namespace vocabulary_core
{
	int workspace_menu_top_bar::on_post_construct()
	{
		using namespace utils::ui;
		//add_item("Back", [self = this]() {
		//	self->app().menu_manager().back();
		//});
		m_layout = create<horizontal_layout>();
		auto actions_menu = create<menu_list>(m_layout.get());
		actions_menu->set_title("Actions");
		actions_menu->add_item("New Word", [self = this]() {
			workspace_menu_controller::open(self->app(), {"new_word"});
		});
		actions_menu->add_item("Random Word Game", [self = this]() {
			workspace_menu_controller::open(self->app(), {"random_word_game"});
		});
		actions_menu->add_item("Library", [self = this]() {
			workspace_menu_controller::open(self->app(), {"library"});
		});
		actions_menu->add_item("Settings", [self = this]() {
			workspace_menu_controller::open(self->app(), {"settings"});
		});
		auto settings_button = create<button>(m_layout.get());
		settings_button->set_text("Settings");
		settings_button->set_on_click([self = this](bool up) {
			workspace_menu_controller::open(self->app(), {"settings"});
		});
		 //add_item("Settings", [self = this]() {
		 //	workspace_menu_controller::open_on_top(self->app(), {"settings"});
		 //});
		return 0;
	}

	utils::ui::layout_ptr workspace_menu_top_bar::layout() const {
		return m_layout->as_ptr<utils::ui::layout>();
	}
}