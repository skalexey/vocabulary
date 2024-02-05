#pragma once

#include <abstract_ui/final/widgets/menu.h>
#include <abstract_ui/fwd.h>

namespace vocabulary_core
{
	class main_menu : public utils::ui::final::menu
	{
		using base = utils::ui::final::menu;

		public:
			main_menu();
			main_menu(const utils::ui::menu_ptr& impl);
			utils::ui::button& settings_button() { return *m_settings_button; }
			utils::ui::button& new_word_button() { return *m_new_word_button; }
			utils::ui::button& play_random_word_button() { return *m_play_random_word_button; }
			utils::ui::button& add_word_button() { return *m_add_word_button; }
			utils::ui::button& library_button() { return *m_library_button; }

		private:
			int this_on_post_construct();
			void construct();
			
		private:
			utils::ui::button_ptr m_settings_button;
			utils::ui::button_ptr m_new_word_button;
			utils::ui::button_ptr m_play_random_word_button;
			utils::ui::button_ptr m_add_word_button;
			utils::ui::button_ptr m_library_button;
	};
}