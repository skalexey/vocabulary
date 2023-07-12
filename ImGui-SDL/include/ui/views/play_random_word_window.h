#pragma once

#include <utils/ui/imgui/fwd.h>
#include <utils/ui/imgui/widgets/dialog.h>
#include <core/include/ui/views/play_random_word_window.h>

class play_random_word_window : public utils::ui::imgui::dialog, public vocabulary_core::play_random_word_window
{
public:
	using base = vocabulary_core::play_random_word_window;
	
private:
	WIDGET_REGISTRATOR(utils::ui::imgui::widget_factory, play_random_word_window);
	std::shared_ptr<play_random_word_window> m_ptr;
};
