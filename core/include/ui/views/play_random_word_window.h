#pragma once

#include <utils/ui/widgets/dialog.h>
#include <utils/ui/fwd.h>

namespace vocabulary_core
{
	class play_random_word_window : public virtual utils::ui::dialog
	{
		using base = utils::ui::dialog;

		public:
			play_random_word_window();
			utils::ui::text& example_label() { return *m_example_label; }
			utils::ui::text& translation_label() { return *m_translation_label; }
			utils::ui::label& word_label() { return *m_word_label; }
			utils::ui::button& show_example_button() { return *m_show_example_button; }
			utils::ui::button& show_translation_button() { return *m_show_translation_button; }
			utils::ui::button& i_know_it_button() { return *m_i_know_it_button;}
			utils::ui::button& skip_button() { return *m_skip_button; }

		private:
			int this_on_post_construct();
			
		private:
			utils::ui::label_ptr m_word_label;
			utils::ui::text_ptr m_example_label;
			utils::ui::text_ptr m_translation_label;
			utils::ui::button_ptr m_show_example_button;
			utils::ui::button_ptr m_show_translation_button;
			utils::ui::button_ptr m_i_know_it_button;
			utils::ui::button_ptr m_skip_button;
	};
}