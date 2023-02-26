
#pragma once

#include <deque>
#include <string>
#include "WindowController.h"
#include "ui/views/PlayRandomWordWindow.h"
#include "word.h"

class PlayRandomWordController : public WindowController
{
public:
	PlayRandomWordController();
	void Show();
	ImGui::PlayRandomWordWindow& View() { return m_view; }
	void ShowRandomWord();

protected:
	word& CurrentWord();

private:
	ImGui::PlayRandomWordWindow m_view;
	std::deque<std::string> m_words_queue;
	std::string m_current_word;
	bool m_example_shown = false;
	bool m_translation_shown = false;
};
