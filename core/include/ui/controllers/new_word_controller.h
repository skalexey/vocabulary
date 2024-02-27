
#pragma once

#include <deque>
#include <string>
#include <memory>
#include "ui/controllers/view_controller.h"
#include "ui/views/new_word_window.h"

class word;

namespace vocabulary_core
{
	class app;

	class new_word_controller : public vocabulary_core::view_controller
	{
		using base = vocabulary_core::view_controller;

	public:
		new_word_window& view() {
			return dynamic_cast<new_word_window&>(base::view());
		}

	protected:
		int on_post_construct() override;
	};
	using new_word_controller_ptr = std::shared_ptr<new_word_controller>;
}
