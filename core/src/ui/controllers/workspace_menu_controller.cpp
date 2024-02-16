#include <abstract_ui/widget_factory.h>
#include <abstract_ui/menu_manager.h>
#include "ui/controllers/workspace_menu_controller.h"
#include "ui/views/workspace_menu.h"
#include "app.h"
#include <utils/Log.h>
LOG_TITLE("workspace_menu_controller");

namespace vocabulary_core
{
	int workspace_menu_controller::on_post_construct()
	{
		set_view(std::dynamic_pointer_cast<utils::ui::menu>(get_factory().create_final<vocabulary_core::workspace_menu>(app())));
		return 0;
	}
}
