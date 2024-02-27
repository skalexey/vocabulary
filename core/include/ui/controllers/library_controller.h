
#pragma once

#include <memory>
#include <abstract_ui/view_controller.h>
#include "ui/controllers/view_controller.h"
#include "ui/views/library_window.h"

namespace vocabulary_core
{
	class library_controller : public vocabulary_core::view_controller
	{
		using base = vocabulary_core::view_controller;

	public:
		library_window& view() {
			return dynamic_cast<library_window&>(base::view());
		}

	protected:
		int on_post_construct() override;
	};
	using library_controller_ptr = std::shared_ptr<library_controller>;
}
