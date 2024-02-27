#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/app.h>
#include <abstract_ui/menu_manager.h>
#include <utils/Log.h>
#include "ui/views/main_menu.h"
#include "app.h"
#include "ui/controllers/workspace_menu_controller.h"
#include "ui/controllers/main_menu_controller.h"
LOG_TITLE("main_menu_controller");

namespace vocabulary_core
{
	int main_menu_controller::on_post_construct()
	{
		set_view<vocabulary_core::main_menu>(&app());
		view().settings_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("settings_button clicked");
			workspace_menu_controller::open(self->app(), {"settings"});
		});
		view().new_word_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("new_word_button clicked");
			workspace_menu_controller::open(self->app(), {"new_word"});
		});
		view().play_random_word_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("play_random_word_button clicked");
			workspace_menu_controller::open(self->app(), {"random_word_game"});
		});
		view().library_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("library_button clicked");
			workspace_menu_controller::open(self->app(), {"library"});
		});
		return 0;
	}

	vocabulary_core::app& main_menu_controller::app()
	{
		return dynamic_cast<vocabulary_core::app&>(base::app());
	}

	const vocabulary_core::app& main_menu_controller::get_app() const
	{
		return dynamic_cast<const vocabulary_core::app&>(base::get_app());
	}
}
