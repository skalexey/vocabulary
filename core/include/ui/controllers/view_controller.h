#pragma once

#include <abstract_ui/view_controller.h>
#include "fwd.h"

namespace vocabulary_core
{
	class view_controller : public utils::ui::view_controller
	{
	public:
		vocabulary_core::app& app();
		const vocabulary_core::app& get_app() const;
	};
}