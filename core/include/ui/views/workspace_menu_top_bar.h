#pragma once

#include <abstract_ui/final/widgets/menu_bar.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class workspace_menu_top_bar : public utils::ui::final::menu_bar
	{
	public:
		using base = utils::ui::final::menu_bar;

		protected:
			int on_post_construct() override;
	};
}