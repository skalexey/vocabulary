#pragma once

#include <utils/ui/imgui/widgets/dialog.h>
#include <utils/ui/imgui/widgets/button.h>
#include <utils/ui/imgui/widgets/label.h>
#include <utils/ui/imgui/widgets/text.h>
#include <utils/ui/imgui/widget_factory.h>

// TODO: bring some abstraction
class play_random_word_window : public utils::ui::imgui::dialog
{
	using base = utils::ui::imgui::dialog;

	public:
		play_random_word_window()
			: m_show_example_button("show Example")
			, m_show_translation_button("show Translation")
			, m_i_know_it_button("I Know It")
			, m_skip_button("Skip")
		{
			// set_modal(false);
			// set_auto_resize(true);
			set_size({ 500, 700 });
			set_title("Random Word Game");
			set_on_show([this]() {
				m_word_label.show();
				m_example_label.show();
				m_translation_label.show();
				m_show_example_button.show();
				m_show_translation_button.show();
				m_i_know_it_button.show();
				m_skip_button.show();
			});
		}

		utils::ui::imgui::text& example_label() { return m_example_label; }
		utils::ui::imgui::text& translation_label() { return m_translation_label; }
		utils::ui::imgui::label& word_label() { return m_word_label; }
		utils::ui::imgui::button& show_example_button() { return m_show_example_button; }
		utils::ui::imgui::button& show_translation_button() { return m_show_translation_button; }
		utils::ui::imgui::button& i_know_it_button() { return m_i_know_it_button;}
		utils::ui::imgui::button& skip_button() { return m_skip_button; }

	protected:
		void on_show() override {
			base::on_show();
		}

	private:
		utils::ui::imgui::label m_word_label;
		utils::ui::imgui::text m_example_label;
		utils::ui::imgui::text m_translation_label;
		utils::ui::imgui::button m_show_example_button;
		utils::ui::imgui::button m_show_translation_button;
		utils::ui::imgui::button m_i_know_it_button;
		utils::ui::imgui::button m_skip_button;
};
