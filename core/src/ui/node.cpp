#include "app.h"
#include "ui/node.h"

namespace vocabulary_core
{
	vocabulary_core::app& vocabulary_core::node::app()
	{
		return dynamic_cast<vocabulary_core::app&>(base::app());
	}

	const vocabulary_core::app& node::get_app() const
	{
		return dynamic_cast<const vocabulary_core::app&>(base::get_app());
	}
}