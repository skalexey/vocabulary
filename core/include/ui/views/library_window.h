#pragma once

#include <abstract_ui/final/widgets/dialog.h>
#include <abstract_ui/fwd.h>
#include <abstract_ui/structure/list.h>
#include "ui/node.h"

namespace vocabulary_core
{
	using namespace utils::ui;
	class library_window : public final::dialog
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
			image_ptr image;
		};

		struct word_row
		{
			word_row() = default;
			word_row(utils::ui::node* owner) {
				init(owner);
			}
			word_row(utils::ui::node* owner, const std::string& value, char level, const std::function<void(bool)>& on_click) {
				init(owner, value, level, on_click);
			}
			void init(utils::ui::node* owner);
			void init(utils::ui::node* owner, const std::string& value, char level, const std::function<void(bool)>& on_click);
			widget_ptr root;
			horizontal_layout_ptr layout;
			button_ptr word;
			knowledge_level_struct knowledge_level;
		};

		using words_list_t = utils::ui::structure::vector<word_row>;
		words_list_t words_list{ this };

	private:
		int on_post_construct() override;
	};
}