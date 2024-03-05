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
		{
			auto& child_view = child_controller->view();
			child_view.set_modal(true);
			child_view.set_vertical_alignment(utils::ui::widget::alignment::center);
			child_view.set_horizontal_alignment(utils::ui::widget::alignment::center);
		}
	}

	void workspace_menu_controller::process_open_options(const vl::Object& options)
	{
		if (options.Has("open_list"))
		{
			bool on_top = options.Has("on_top") && options["on_top"].AsBool().Val();
			auto open_list = options["open_list"].AsList();
			for (int i = 0; i < open_list.Size(); i++)
			{
				auto&& element = open_list[i];
				auto&& what_to_open = element.AsString().Val();
				LOG_DEBUG("Open '" << what_to_open << "'");
				if (what_to_open == "new_word")
				{
					create_view_controller<new_word_controller>(*this, on_top);
				}
				else if (what_to_open == "random_word_game")
				{
					create_view_controller<play_random_word_controller>(*this, on_top);
				}
				else if (what_to_open == "library")
				{
					create_view_controller<library_controller>(*this, on_top);
				}
				else if (what_to_open == "settings")
				{
					create_view_controller<settings_controller>(*this, on_top);
				}
				else
				{
					LOG_ERROR("Unknown option: " << what_to_open);
					assert(false && "Unknown option");
				}
			}
		}
	}

	void workspace_menu_controller::open(utils::ui::app& app, const std::vector<std::string>& open_list, bool add)
	{
		vl::Object options;
		if (!open_list.empty())
		{
			vl::List open_list_vl;
			for (auto&& what_to_open : open_list)
				open_list_vl.Add(what_to_open);
			options["open_list"] = open_list_vl;
		}
		if (add)
		{
			auto& stack_top = app.menu_manager().get_menu_stack().back();
			assert(stack_top.name == "workspace_menu");
			app.menu_manager().current_menu().process_event("open", options);
		}
		else
			app.menu_manager().open_menu("workspace_menu", options);
	}

	void workspace_menu_controller::add(utils::ui::app& app, const std::vector<std::string>& add_list)
	{
		open(app, add_list, true);
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
