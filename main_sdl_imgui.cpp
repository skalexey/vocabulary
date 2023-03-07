// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// Important to understand: SDL_Renderer is an _optional_ component of SDL. We do not recommend you use SDL_Renderer
// because it provide a rather limited API to the end-user. We provide this backend for the sake of completeness.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.

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
