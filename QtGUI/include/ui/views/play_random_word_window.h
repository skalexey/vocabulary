#pragma once

#include <memory>
#include <abstract_ui/qt/fwd.h>
#include <abstract_ui/qt/widgets/dialog.h>
#include <core/include/ui/views/play_random_word_window.h>

class play_random_word_window : public utils::ui::qt::dialog, public vocabulary_core::play_random_word_window, public std::enable_shared_from_this<play_random_word_window>
{
public:
	using base = vocabulary_core::play_random_word_window;

	void on_show() override {
		utils::ui::qt::dialog::on_show();
	}

private:
	WIDGET_REGISTRATOR(utils::ui::qt::widget_factory, play_random_word_window);

private:
	std::shared_ptr<play_random_word_window> m_ptr;
};
