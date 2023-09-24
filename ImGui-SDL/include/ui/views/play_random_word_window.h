#pragma once

#include <abstract_ui/imgui/fwd.h>
#include <abstract_ui/imgui/widgets/dialog.h>
#include <core/include/ui/views/play_random_word_window.h>

class play_random_word_window : public utils::ui::imgui::dialog, public vocabulary_core::play_random_word_window
{
public:
	using base = vocabulary_core::play_random_word_window;
};
