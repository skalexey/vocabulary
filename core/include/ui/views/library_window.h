#pragma once

#include <abstract_ui/final/widgets/dialog.h>
#include <abstract_ui/fwd.h>
#include "ui/node.h"

namespace vocabulary_core
{
	class library_window : public utils::ui::final::dialog, public virtual vocabulary_core::node
	{
		using base = utils::ui::final::dialog;

		private:
			int on_post_construct() override;
	};
}