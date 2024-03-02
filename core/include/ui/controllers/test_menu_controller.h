
#pragma once

#include <deque>
#include <string>
#include <memory>
#include <abstract_ui/menu_controller.h>
#include "ui/views/test_menu.h"

class word;

namespace vocabulary_core
{
	class app;

	class test_menu_controller : public utils::ui::menu_controller
	{
		using base = utils::ui::menu_controller;

	public:
		test_menu& view() {
			return dynamic_cast<test_menu&>(base::view());
		}

		vocabulary_core::app& app();
		const vocabulary_core::app& get_app() const;

	protected:
		int on_post_construct() override;
		void create();
	};
	using test_menu_controller_ptr = std::shared_ptr<test_menu_controller>;
}
