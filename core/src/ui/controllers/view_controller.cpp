#include "app.h"
#include "ui/controllers/view_controller.h"

namespace vocabulary_core
{
	vocabulary_core::app& vocabulary_core::view_controller::app()
	{
		return dynamic_cast<vocabulary_core::app&>(base::app());
	}

	const vocabulary_core::app& view_controller::get_app() const
	{
		return dynamic_cast<const vocabulary_core::app&>(base::get_app());
	}
}