#pragma once

#include <functional>
#include <utils/imgui/Window.h>
#include <utils/imgui/Widgets/Button.h>
#include <utils/imgui/Widgets/Label.h>

namespace ImGui
{
	class PlayRandomWordWindow : public utils::imgui::Window
	{
		public:
			PlayRandomWordWindow()
				: Window({0.25f, 0.f}, {0.75f, 1.f})
				, m_show_example_button("Show Example")
				, m_show_translation_button("Show Translation")
				, m_i_know_it_button("I Know It")
			{}

			using on_select_t = std::function<void(int)>;
			const char* Title() const override { return "Random Word Game"; }

			ImGui::LabelWidget& ExampleLabel() { return m_example_label; }
			ImGui::LabelWidget& TranslationLabel() { return m_translation_label; }
			ImGui::LabelWidget& WordLabel() { return m_word_label; }
			ImGui::ButtonWidget& ShowExampleButton() { return m_show_example_button; }
			ImGui::ButtonWidget& ShowTranslationButton() { return m_show_translation_button;}
			ImGui::ButtonWidget& IKnowItButton() { return m_i_know_it_button;}

		protected:
			void onShow() override;

		private:
			ImGui::LabelWidget m_word_label;
			ImGui::LabelWidget m_example_label;
			ImGui::LabelWidget m_translation_label;
			ImGui::ButtonWidget m_show_example_button;
			ImGui::ButtonWidget m_show_translation_button;
			ImGui::ButtonWidget m_i_know_it_button;
	};
}