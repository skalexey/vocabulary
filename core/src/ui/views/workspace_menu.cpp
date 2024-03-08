#include <abstract_ui/widgets/layouts/auto_layout.h>
#include <utils/log.h>
#include "ui/views/workspace_menu_top_bar.h"
#include "ui/views/workspace_menu.h"
LOG_TITLE("vocabulary_core::workspace_menu");

namespace vocabulary_core
{
	int workspace_menu::on_post_construct()
	{
		base::on_post_construct();
		using namespace utils::ui;
		m_top_bar = create_final<workspace_menu_top_bar>();
		m_content_layout = create<auto_layout>();
		set_title("Workspace Menu");
		return 0;
	}
}