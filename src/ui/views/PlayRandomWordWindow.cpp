#include "ui/views/PlayRandomWordWindow.h"

namespace ImGui
{
	void PlayRandomWordWindow::onShow() {
        m_word_label.Show();
		m_example_label.Show();
		m_translation_label.Show();
		m_show_example_button.Show();
        m_show_translation_button.Show();
        m_i_know_it_button.Show();
	}
}