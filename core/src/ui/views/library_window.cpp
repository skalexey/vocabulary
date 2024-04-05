#include <string>
#include <abstract_ui/app.h>
#include <abstract_ui/widget.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/image.h>
#include <abstract_ui/widgets/layouts/horizontal_layout.h>
#include <utils/log.h>
#include "word.h"
#include "ui/views/library_window.h"

LOG_TITLE("library_window");

namespace
{
	std::string level_texture_by_level(char level)
	{
		const int max_levels = 4;
		return "knowledge_level_" + std::to_string(int(std::round((float(level) / word::level_max) * (max_levels - 1)))) + ".png";
	}
}

namespace vocabulary_core
{
	int library_window::on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::automatic, size_policy::automatic);
		// Not every implementation supports automatic resize properly
		set_modal(false);
		set_title("Library");
		set_max_width(250);
		return 0;
	}

	void library_window::knowledge_level_struct::init(utils::ui::node* owner)
	{
		root = owner->create<utils::ui::widget>();
		image = root->create<utils::ui::image>();
		image->set_size({ 16, 16 });
		root->set_size({ 16, 16 });
	}
	
	void library_window::word_row::init(utils::ui::node* owner)
	{
		auto layout = owner->create<horizontal_layout>();
		root = layout;
		word = layout->create<button>();
		knowledge_level.init(layout.get());
	}

	void library_window::word_row::init(utils::ui::node* owner, const std::string& value, char level, const std::function<void(bool)>& on_click)
	{
		init(owner);
		word->set_text(value);
		knowledge_level.image->set_texture(level_texture_by_level(level));
		word->set_on_click(on_click);
	}
}