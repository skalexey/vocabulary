
#pragma once

#include <deque>
#include <string>
#include <memory>
#include <abstract_ui/menu_controller.h>
#include "ui/views/main_menu.h"

class word;

namespace vocabulary_core
{
	class app;

	class main_menu_controller : public utils::ui::menu_controller
	{
		using base = utils::ui::menu_controller;

	public:
		main_menu& view() {
			return *std::dynamic_pointer_cast<main_menu>(get_view());
		}

		vocabulary_core::app& app();
		const vocabulary_core::app& get_app() const;

	protected:
		int on_post_construct() override;
	};
	using main_menu_controller_ptr = std::shared_ptr<main_menu_controller>;
}
