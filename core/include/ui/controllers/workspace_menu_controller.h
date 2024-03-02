
#pragma once

#include <vl_fwd.h>
#include <abstract_ui/fwd.h>
#include <abstract_ui/menu_controller.h>
#include "ui/views/workspace_menu.h"

namespace vocabulary_core
{
	class workspace_menu_controller : public utils::ui::menu_controller
	{
		using base = utils::ui::menu_controller;

	public:
		workspace_menu& view() {
			return dynamic_cast<workspace_menu&>(base::view());
		}

		static void open(utils::ui::app& app, const std::vector<std::string>& open_list = {}, bool add = false);
		static void add(utils::ui::app& app, const std::vector<std::string>& add_list = {});
		static void open_on_top(utils::ui::app& app, const std::string& what);
		bool process_event(const std::string& name, const vl::Object& data) override;

	protected:
		int on_post_construct() override;
		void process_open_options(const vl::Object& options);
	};
	using workspace_menu_controller_ptr = std::shared_ptr<workspace_menu_controller>;
}
