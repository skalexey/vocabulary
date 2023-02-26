// 
// Application UI logic controller.

#pragma once

#include "ui/controllers/PlayRandomWordController.h"

class App
{
public:
	int Run();
	void Show();

private:
	WindowControllerPtr m_window_ctrl;
};

// Definitions
int App::Run() {
	m_window_ctrl = std::make_unique<PlayRandomWordController>();
	return 0;
}

void App::Show() {
	m_window_ctrl->Show();
}

