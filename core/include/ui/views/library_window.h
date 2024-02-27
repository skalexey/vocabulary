#pragma once

#include <abstract_ui/final/widgets/dialog.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class library_window : public utils::ui::final::dialog
	{
		using base = utils::ui::final::dialog;

		private:
			int on_post_construct() override;
	};
}