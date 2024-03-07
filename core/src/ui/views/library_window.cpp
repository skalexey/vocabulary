#include <abstract_ui/app.h>
#include <abstract_ui/widget.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/image.h>
#include <abstract_ui/widgets/layouts/horizontal_layout.h>
#include <utils/Log.h>
#include "ui/views/library_window.h"

LOG_TITLE("library_window");

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
		image_wrapper = owner->create<utils::ui::widget>();
		root = image_wrapper;
		image = image_wrapper->create<utils::ui::image>();
	}
	
	void library_window::word_row::init(utils::ui::node* owner)
	{
		auto layout = owner->create<horizontal_layout>();
		root = layout;
		word = layout->create<button>();
		knowledge_level.init(layout.get());
	}
}