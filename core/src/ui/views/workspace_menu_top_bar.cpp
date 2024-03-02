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
		add_item("Back", [self = this]() {
			self->app().menu_manager().back();
		});
		auto actions_menu = create<menu_list>();
		actions_menu->set_title("Add");
		actions_menu->add_item("New Word", [self = this]() {
			workspace_menu_controller::add(self->app(), {"new_word"});
		});
		actions_menu->add_item("Random Word Game", [self = this]() {
			workspace_menu_controller::add(self->app(), {"random_word_game"});
		});
		actions_menu->add_item("Library", [self = this]() {
			workspace_menu_controller::add(self->app(), {"library"});
		});
		actions_menu->add_item("Settings", [self = this]() {
			workspace_menu_controller::add(self->app(), {"settings"});
		});
		add_item("Settings", [self = this]() {
			workspace_menu_controller::open(self->app(), {"settings"});
		});
		return 0;
	}
}