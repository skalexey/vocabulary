// TODO: figure out why SDL.h include is needed on Android (it just a stuck without it)
#include <SDL.h>
#include "app.h"

app* g_app = nullptr;

// Used in utils/networking/sync_resources.h
void ask_user(const std::string& question, const std::function<void(bool)>& on_answer, const char* yes_btn_text = nullptr, const char* no_btn_text = nullptr)
{
	if (g_app)
		g_app->ask_user(question, on_answer, yes_btn_text, no_btn_text);
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
