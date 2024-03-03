#pragma once

#include <abstract_ui/node.h>
#include "fwd.h"

namespace vocabulary_core
{
	class node : public virtual utils::ui::node
	{
	public:
		using base = utils::ui::node;
		vocabulary_core::app& app();
		const vocabulary_core::app& get_app() const;
	};
}