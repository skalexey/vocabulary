
#pragma once

#include <abstract_ui/menu_controller.h>
#include "ui/views/workspace_menu.h"

namespace vocabulary_core
{
	class workspace_menu_controller : public utils::ui::menu_controller
	{
		using base = utils::ui::menu_controller;

	public:
		workspace_menu& view() {
			return *std::dynamic_pointer_cast<workspace_menu>(get_view());
		}

	protected:
		int on_post_construct() override;
	};
	using workspace_menu_controller_ptr = std::shared_ptr<workspace_menu_controller>;
}
