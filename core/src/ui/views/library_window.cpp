#include <abstract_ui/app.h>
#include <abstract_ui/widgets/dialog.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/library_window.h"

namespace vocabulary_core
{
	int library_window::on_post_construct()
	{
		using namespace utils::ui;
		// Let the implementation decide how to manage the size
		set_size_policy(size_policy::type::automatic, size_policy::type::automatic);
		// Not every implementation support automatic resize properly
		set_size({ 320, 240 });
		set_modal(false);
		set_title("Library");
		set_max_width(250);
		return 0;
	}
}