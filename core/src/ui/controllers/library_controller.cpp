#include <utils/Log.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/app.h>
#include "ui/views/library_window.h"
#include "app.h"
#include "words.h"
#include "word.h"
#include "ui/controllers/library_controller.h"
LOG_TITLE("library_controller");

extern words g_words;

namespace vocabulary_core
{
	int library_controller::on_post_construct()
	{
		set_view<vocabulary_core::library_window>();
		return 0;
	}
}
