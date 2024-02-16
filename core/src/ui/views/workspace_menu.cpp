#include <abstract_ui/app.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widget_factory.h>
#include "ui/views/workspace_menu.h"
#include "ui/views/workspace_menu_top_bar.h"
#include <utils/Log.h>
LOG_TITLE("vocabulary_core::workspace_menu");

namespace vocabulary_core
{
	int workspace_menu::on_post_construct()
	{
		using namespace utils::ui;
		set_title("Workspace Menu");
		m_top_bar = create_final<workspace_menu_top_bar>();
		// bool ForeachProp(const std::function<bool(const std::string&, const vl::Var&)>& pred, bool recursive = false) const;
		if (m_options && !m_options.IsEmpty())
		{
			auto open_list = m_options["open"].AsList();
			for (int i = 0; i < open_list.Size(); i++)
			{
				LOG_DEBUG("Open '" << open_list[i].AsString() << "'");
				// Open every window in the list
			}
		}
		return 0;
	}
}