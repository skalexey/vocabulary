#include <cmath>
#include <random>
#include <algorithm>
#include <utils/Log.h>
#include "words.h"
#include "ui/controllers/PlayRandomWordController.h"

LOG_PREFIX("[PlayRandomWordController]: ");
LOG_POSTFIX("\n");

extern words g_words;

PlayRandomWordController::PlayRandomWordController() {
	m_view.ShowExampleButton().SetOnClick([this] {
		LOG_DEBUG("ShowExampleButton");
		if (m_current_word.empty())
			return;
		m_view.ExampleLabel().SetText(CurrentWord().get_example());
		m_example_shown = true;
	});
	m_view.ShowTranslationButton().SetOnClick([this] {
		LOG_DEBUG("ShowTranslationButton");
		if (m_current_word.empty())
			return;
		auto& w = CurrentWord();
		m_view.TranslationLabel().SetText(!w.get_translation().empty() ? std::string(w.get_translation().begin(), w.get_translation().end()) : "no translation");
		m_translation_shown = true;
	});
	m_view.IKnowItButton().SetOnClick([this] {
		LOG_DEBUG("IKnowItButton");
		if (m_current_word.empty())
			return;
		auto& w = CurrentWord();
		float example_cost = m_example_shown ? 0.5f : 0.0f;
		float translation_cost = m_translation_shown ? 1.f : 0.f;
		auto m = std::max(0.f, (1.0f - example_cost - translation_cost));
		w.set_level(char(word::level_max * m));
		g_words.update_local_storage();
		m_example_shown = false;
		m_translation_shown = false;
		ShowRandomWord();
	});
	ShowRandomWord();
}

void PlayRandomWordController::ShowRandomWord()
{
	if (g_words.list.empty()) {
		LOG_DEBUG("ShowRandomWord(): No words");
		return;
	}
	if (m_words_queue.empty()) {
		std::for_each(g_words.list.begin(), g_words.list.end(), [this](const auto& pair) {
			if (pair.second.get_level() < word::level_max)
				m_words_queue.push_back(pair.first);
		});
		std::shuffle(m_words_queue.begin(), m_words_queue.end(), std::random_device());
	}
	m_view.TranslationLabel().SetText("");
	m_view.ExampleLabel().SetText("");
	if (m_words_queue.empty())
	{
		m_view.ExampleLabel().SetText("Congratulations!!! You know all the words!");
		return;
	}
	m_current_word = m_words_queue.back();
	m_view.WordLabel().SetText(m_current_word);
	m_words_queue.pop_back();
}

word& PlayRandomWordController::CurrentWord()
{
	return g_words.list.value(m_current_word);
}

void PlayRandomWordController::Show()
{
	m_view.Show();
}
