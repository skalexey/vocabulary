#include <utils/Log.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/app.h>
#include "app.h"
#include "words.h"
#include "word.h"
#include "ui/controllers/settings_controller.h"
LOG_TITLE("settings_controller");

extern words g_words;

namespace vocabulary_core
{
	int settings_controller::on_post_construct()
	{
		set_view<vocabulary_core::settings_window>();
		return 0;
	}
}
