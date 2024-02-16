
#pragma once

#include <deque>
#include <string>
#include <memory>
#include <abstract_ui/view_controller.h>
#include "ui/views/new_word_window.h"

class word;

namespace vocabulary_core
{
	class app;

	class new_word_controller : public utils::ui::view_controller
	{
		using base = utils::ui::view_controller;

	public:
		new_word_window& view() {
			return *std::dynamic_pointer_cast<new_word_window>(get_view());
		}

		vocabulary_core::app& app();
		const vocabulary_core::app& get_app() const;

	protected:
		int on_post_construct() override;
	};
	using new_word_controller_ptr = std::shared_ptr<new_word_controller>;
}
