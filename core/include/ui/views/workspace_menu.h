#pragma once

#include <VL.h>
#include <abstract_ui/final/widgets/menu.h>
#include <abstract_ui/fwd.h>
#include "fwd.h"

namespace vocabulary_core
{
	class workspace_menu : public utils::ui::final::menu
	{
		using base = utils::ui::final::menu;

		public:
			workspace_menu_top_bar& top_bar() { return *m_top_bar; }

		protected:
			int on_post_construct() override;
			
		private:
			workspace_menu_top_bar_ptr m_top_bar;
			vl::Object m_options;
	};
}