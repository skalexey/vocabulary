
#pragma once
#include <cassert>
#include <memory>
#include <utils/ui/Window.h>

class WindowController;
using WindowControllerPtr = std::unique_ptr<WindowController>;

class WindowController
{
public:
	WindowController() = default;

	virtual void Show() {
		assert(m_view);
		m_view->Show();
	}
protected:
	void setView(utils::ui::WindowPtr&& view) {
		m_view = std::move(view);
	}

private:
	utils::ui::WindowPtr m_view;
};
