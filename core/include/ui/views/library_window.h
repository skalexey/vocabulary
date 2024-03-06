#pragma once

#include <abstract_ui/final/widgets/dialog.h>
#include <abstract_ui/fwd.h>
#include "ui/node.h"

namespace vocabulary_core
{
	using namespace utils::ui;
	class library_window : public final::dialog, public virtual vocabulary_core::node
	{
	public:
		using base = final::dialog;

		struct knowledge_level_struct
		{
			knowledge_level_struct() = default;
			knowledge_level_struct(utils::ui::node* owner) {
				init(owner);
			}
			void init(utils::ui::node* owner);
			widget_ptr root;
			widget_ptr image_wrapper;
			image_ptr image;
		};

		struct word_row
		{
			word_row() = default;
			word_row(utils::ui::node* owner) {
				init(owner);
			}
			void init(utils::ui::node* owner);
			widget_ptr root;
			horizontal_layout_ptr layout;
			button_ptr word;
			knowledge_level_struct knowledge_level;
		};

	private:
		int on_post_construct() override;
	};
}