// TODO: figure out why SDL.h include is needed on Android (it just a stuck without it)
#include <SDL.h>
#include <utils/common.h>
#include "app.h"

app* g_app = nullptr;

// Used in utils/networking/sync_resources.h
void ask_user(
    const std::string& question
    , const utils::void_bool_cb& on_answer
    , const char* yes_btn_text = nullptr
    , const char* no_btn_text = nullptr
)
{
	if (g_app)
		g_app->ask_user(question, on_answer, yes_btn_text, no_btn_text);
}

void ask_line(
	const std::string& msg
	, const utils::void_string_bool_cb& on_answer
	, const std::string& default_value = {}
	, const char* ok_btn_text = nullptr
	, const char* cancel_btn_text = nullptr
)
{
    if (g_app)
        g_app->ask_line(msg, on_answer, default_value, ok_btn_text, cancel_btn_text);
}

void request_auth(
	const std::string& user_name
	, const std::string& token
	, const utils::void_int_cb& on_result
)
{
	if (g_app)
		g_app->request_auth(user_name, token, on_result);
}

// Main code
int main(int, char**)
{
	app app;
	g_app = &app;
	auto r = app.run();
	g_app = nullptr;
	return r;
}
