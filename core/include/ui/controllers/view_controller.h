#pragma once

#include <abstract_ui/view_controller.h>
#include "ui/node.h"
#include "fwd.h"

namespace vocabulary_core
{
	class view_controller : public virtual vocabulary_core::node, public virtual utils::ui::view_controller
	{
	};
}