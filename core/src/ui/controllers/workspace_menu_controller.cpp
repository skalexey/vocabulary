#include <VL.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/layouts/auto_layout.h>
#include <abstract_ui/menu_manager.h>
#include "ui/controllers/workspace_menu_controller.h"
#include "ui/views/workspace_menu.h"
#include "ui/controllers/new_word_controller.h"
#include "ui/controllers/play_random_word_controller.h"
#include "ui/controllers/library_controller.h"
#include "ui/controllers/settings_controller.h"
#include "app.h"
#include <utils/Log.h>
LOG_TITLE("workspace_menu_controller");

namespace vocabulary_core
{
	int workspace_menu_controller::on_post_construct()
	{
		set_view<vocabulary_core::workspace_menu>(&app());
		process_open_options(get_options());
		return 0;
	}

	template <typename T>
	void create_view_controller(workspace_menu_controller& self, bool on_top = false)
	{
		vl::Object options;
		utils::ui::node* view_parent = on_top ? &self.view().as<utils::ui::node>() : &self.view().content_layout().as<utils::ui::node>();
		options["view_parent"] = view_parent;
		auto child_controller = self.create_child_view_controller<T>(options);
		if (on_top)
			child_controller->view().set_modal(true);
	}

	void workspace_menu_controller::process_open_options(const vl::Object& options)
	{
		if (options.Has("open_list"))
		{
			auto open_list = options["open_list"].AsList();
			for (int i = 0; i < open_list.Size(); i++)
			{
				auto&& what_to_open = open_list[i].AsString().Val();
				LOG_DEBUG("Open '" << what_to_open << "'");
				if (what_to_open == "new_word")
				{
					create_view_controller<new_word_controller>(*this);
				}
				else if (what_to_open == "random_word_game")
				{
					create_view_controller<play_random_word_controller>(*this);
				}
				else if (what_to_open == "library")
				{
					create_view_controller<library_controller>(*this);
				}
				else if (what_to_open == "settings")
				{
					create_view_controller<settings_controller>(*this);
				}
				else
				{
					LOG_ERROR("Unknown option: " << what_to_open);
					assert(false && "Unknown option");
				}
			}
		}
	}

	void workspace_menu_controller::open(utils::ui::app& app, const std::vector<std::string>& open_list)
	{
		vl::Object options;
		if (!open_list.empty())
		{
			vl::List open_list_vl;
			for (auto&& what_to_open : open_list)
				open_list_vl.Add(what_to_open);
			options["open_list"] = open_list_vl;
		}
		app.menu_manager().open_menu("workspace_menu", options);
	}

	void workspace_menu_controller::open_on_top(utils::ui::app& app, const std::string& what)
	{
		vl::Object options;
		vl::List open_list;
		open_list.Add(what);
		options["open_list"] = open_list;
		options["on_top"] = true;
		app.menu_manager().open_menu("workspace_menu", options);
	}

	bool workspace_menu_controller::process_event(const std::string& name, const vl::Object& data)
	{
		if (name == "open")
			process_open_options(data);
		return base::process_event(name, data);
	}
}
