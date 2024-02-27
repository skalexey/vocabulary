#pragma once

#include <abstract_ui/final/widget.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class workspace_menu_top_bar : public utils::ui::final::widget
	{
	public:
		using base = utils::ui::final::widget;
		utils::ui::layout_ptr layout() const;

		protected:
			int on_post_construct() override;

		private:
			utils::ui::horizontal_layout_ptr m_layout;
	};
}