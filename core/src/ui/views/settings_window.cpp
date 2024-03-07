#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/settings_window.h"

namespace vocabulary_core
{
	int settings_window::on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::automatic, size_policy::automatic);
		// Not every implementation supports automatic resize properly
		set_size({ 320, 240 });
		set_modal(false);
		set_title("Settings");
		set_max_width(250);
		return 0;
	}
}