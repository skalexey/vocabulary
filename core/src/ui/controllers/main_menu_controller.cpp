#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/app.h>
#include <abstract_ui/menu_manager.h>
#include "ui/controllers/main_menu_controller.h"
#include "ui/views/main_menu.h"
#include "app.h"
#include <utils/Log.h>
LOG_TITLE("main_menu_controller");

namespace vocabulary_core
{
	int main_menu_controller::on_post_construct()
	{
		set_view(std::dynamic_pointer_cast<utils::ui::menu>(get_factory().create_final<vocabulary_core::main_menu>(app())));
		view().settings_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("settings_button clicked");
			vl::Object options;
			vl::List open_list;
			open_list.Add("settings");
			options["open"] = open_list;
			self->app().menu_manager().open_menu("workspace_menu", options);
		});
		view().new_word_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("new_word_button clicked");
		});
		view().play_random_word_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("play_random_word_button clicked");
		});
		view().add_word_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("add_word_button clicked");
		});
		view().library_button().set_on_click([self = this](bool up) {
			LOG_DEBUG("library_button clicked");
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
