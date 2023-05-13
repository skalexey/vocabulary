#pragma once

#include <utils/ui/qt/fwd.h>
#include <utils/ui/qt/widgets/dialog.h>
#include <core/include/ui/views/play_random_word_window.h>

class play_random_word_window : public utils::ui::qt::dialog, public vocabulary_core::play_random_word_window
{
public:
	using base = vocabulary_core::play_random_word_window;

	play_random_word_window(utils::ui::node* parent)
		: utils::ui::qt::dialog(parent)
		, base(parent)
	{}
	
private:
	WIDGET_REGISTRATOR(utils::ui::qt::widget_factory, play_random_word_window);

protected:
	void on_show() override {
		utils::ui::qt::dialog::on_show();
	}
};
