
#pragma once

#include <memory>
#include <abstract_ui/view_controller.h>
#include "ui/controllers/view_controller.h"
#include "ui/views/settings_window.h"

namespace vocabulary_core
{
	class settings_controller : public vocabulary_core::view_controller
	{
		using base = vocabulary_core::view_controller;

	public:
		settings_window& view() {
			return dynamic_cast<settings_window&>(base::view());
		}

	protected:
		int on_post_construct() override;
	};
	using settings_controller_ptr = std::shared_ptr<settings_controller>;
}
