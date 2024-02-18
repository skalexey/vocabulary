#pragma once

#include <abstract_ui/final/widget.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class workspace_menu_top_bar : public utils::ui::final::widget
	{
		using base = utils::ui::final::widget;

		public:
			utils::ui::button& actions_button() { return *m_actions_button; }
			utils::ui::button& settings_button() { return *m_settings_button; }

		protected:
			int on_post_construct() override;
			
		private:
			utils::ui::horizontal_layout_ptr m_layout;
			utils::ui::button_ptr m_actions_button;
			utils::ui::button_ptr m_settings_button;
	};
}