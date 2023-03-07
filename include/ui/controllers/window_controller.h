
#pragma once
#include <cassert>
#include <memory>
#include <utils/ui/window.h>


class window_controller
{
public:
	window_controller() = default;

	virtual bool show() {
		assert(m_view);
		return m_view->show();
	}
protected:
	void set_view(const utils::ui::window_ptr& view) {
		m_view = view;
	}
	const utils::ui::window_ptr& get_view() {
		return m_view;
	}

private:
	utils::ui::window_ptr m_view;
};
using window_controller_ptr = std::shared_ptr<window_controller>;