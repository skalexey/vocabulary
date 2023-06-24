#pragma once

#include <memory>
#include <utils/ui/imgui/fwd.h>
#include <utils/ui/imgui/widgets/dialog.h>
#include <core/include/ui/views/play_random_word_window.h>

class play_random_word_window : public utils::ui::imgui::dialog, public vocabulary_core::play_random_word_window, public std::enable_shared_from_this<play_random_word_window>
{
public:
	using base = vocabulary_core::play_random_word_window;

	play_random_word_window(utils::ui::node* parent)
		: utils::ui::node(parent)
		, base(parent)
		, utils::ui::imgui::dialog(parent)
	{}

	utils::ui::node_ptr base_shared_from_this() override {
		return shared_from_this();
	}

private:
	WIDGET_REGISTRATOR(utils::ui::imgui::widget_factory, play_random_word_window);
	std::shared_ptr<play_random_word_window> m_ptr;
protected:
	void on_show() override {
		utils::ui::imgui::dialog::on_show();
	}
};
