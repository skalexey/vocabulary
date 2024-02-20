#include <abstract_ui/app.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/layouts/horizontal_layout.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/menu_manager.h>
#include <utils/Log.h>
#include "ui/controllers/new_word_controller.h"
#include "ui/controllers/play_random_word_controller.h"
#include "ui/views/workspace_menu_top_bar.h"
#include "app.h"
#include "ui/views/workspace_menu.h"
LOG_TITLE("vocabulary_core::workspace_menu");

namespace vocabulary_core
{
	void workspace_menu::open(utils::ui::app& app, const std::vector<std::string>& open_list)
	{
		vl::Object options;
		if (!open_list.empty())
		{
			vl::List open_list_vl;
			for (auto&& what_to_open : open_list)
				open_list_vl.Add(what_to_open);
			options["open"] = open_list_vl;
		}
		app.menu_manager().open_menu("workspace_menu", options);
	}
	
	int workspace_menu::on_post_construct()
	{
		base::on_post_construct();
		using namespace utils::ui;
		m_top_bar = create_final<workspace_menu_top_bar>();
		// TODO: insert the button in front of the top bar
		create_back_button(&m_top_bar->layout());
		set_title("Workspace Menu");
		auto&& options = get_options();
		if (options && !options.IsEmpty())
		{
			auto open_list = options["open"].AsList();
			for (int i = 0; i < open_list.Size(); i++)
			{
				auto&& what_to_open = open_list[i].AsString().Val();
				LOG_DEBUG("Open '" << what_to_open << "'");
				if (what_to_open == "new_word")
				{
					create_abstract<new_word_controller>();
				}
				else if (what_to_open == "random_word_game")
				{
					create_abstract<play_random_word_controller>();
				}
				else if (what_to_open == "library")
				{
				}
				else if (what_to_open == "settings")
				{
				}
			}
		}
		return 0;
	}
}