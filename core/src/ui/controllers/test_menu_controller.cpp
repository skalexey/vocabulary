#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/menu_bar.h>
#include <abstract_ui/app.h>
#include <abstract_ui/menu_manager.h>
#include <utils/log.h>
#include "ui/views/test_menu.h"
#include "app.h"
#include "ui/controllers/workspace_menu_controller.h"
#include "ui/views/new_word_window.h"
#include "ui/controllers/new_word_controller.h"
#include "ui/controllers/test_menu_controller.h"
LOG_TITLE("test_menu_controller");

namespace vocabulary_core
{
	void test_menu_controller::create()
	{
		// auto menu_bar = get_factory().create<utils::ui::menu_bar>(&app(), nullptr, nullptr, true);
		// menu_bar->post_construct();
		auto test_dialog = get_factory().create_final<new_word_window>(app());
		// menu_bar->add_item("Test button", [self = this]() {
		// 	LOG_DEBUG("Test button clicked");
		// });
		//////////////////
		// set_view<vocabulary_core::test_menu>(&app());
		//view().settings_button().set_on_click([self = this](bool up) {
		//	LOG_DEBUG("settings_button clicked");
		//	workspace_menu_controller::open(self->app(), {"settings"});
		//});
		//view().new_word_button().set_on_click([self = this](bool up) {
		//	LOG_DEBUG("new_word_button clicked");
		//	workspace_menu_controller::open(self->app(), {"new_word"});
		//});
		//view().play_random_word_button().set_on_click([self = this](bool up) {
		//	LOG_DEBUG("play_random_word_button clicked");
		//	workspace_menu_controller::open(self->app(), {"random_word_game"});
		//});
		//view().library_button().set_on_click([self = this](bool up) {
		//	LOG_DEBUG("library_button clicked");
		//	workspace_menu_controller::open(self->app(), {"library"});
		//});
	}

	int test_menu_controller::on_post_construct()
	{
		auto create_button = get_factory().create<utils::ui::button>(&app(), nullptr, nullptr, true);
		create_button->post_construct();
		create_button->set_text("Create");
		create_button->set_on_click([self = this](bool up) {
			LOG_DEBUG("create_button clicked");
			self->create();
		});
		create_button->set_position({100, 400});
		
		auto clear_button = get_factory().create<utils::ui::button>(&app(), nullptr, nullptr, true);
		clear_button->post_construct();
		clear_button->set_text("Clear");
		clear_button->set_on_click([=, self = this](bool up) {
			LOG_DEBUG("clear_button clicked");
			auto children = self->app().children();
			for (auto it = children.begin(); it != children.end();)
			{
				if (*it == clear_button || *it == create_button)
					++it;
				else
					it = children.erase(it);
			}
			children.swap(self->app().children());
		});
		clear_button->set_position({200, 400});

		return 0;
	}

	vocabulary_core::app& test_menu_controller::app()
	{
		return dynamic_cast<vocabulary_core::app&>(base::app());
	}

	const vocabulary_core::app& test_menu_controller::get_app() const
	{
		return dynamic_cast<const vocabulary_core::app&>(base::get_app());
	}
}
