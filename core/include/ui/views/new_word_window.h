#pragma once

#include <abstract_ui/final/widgets/dialog.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class new_word_window : public utils::ui::final::dialog
	{
		using base = utils::ui::final::dialog;

		public:
			new_word_window(const utils::ui::dialog_ptr& impl);
			utils::ui::text_input& example_input() { return *m_example_input; }
			utils::ui::text_input& translation_input() { return *m_translation_input; }
			utils::ui::text_input& word_input() { return *m_word_input; }
			utils::ui::button& store_button() { return *m_store_button; }

		private:
			int this_on_post_construct();
			
		private:
			utils::ui::text_input_ptr m_word_input;
			utils::ui::text_input_ptr m_example_input;
			utils::ui::text_input_ptr m_translation_input;
			utils::ui::button_ptr m_store_button;
	};
}