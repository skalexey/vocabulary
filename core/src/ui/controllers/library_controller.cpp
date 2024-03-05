#include <utils/Log.h>
#include <abstract_ui/widgets/button.h>
#include <abstract_ui/widgets/text_input.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/menu_manager.h>
#include <abstract_ui/menu_controller.h>
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
		using namespace utils::ui;
		set_view<vocabulary_core::library_window>();
		// Display last 10 words in reverse order
		int i = 0;
		for (auto it = g_words.list.rbegin(); it != g_words.list.rend(); ++it, i++)
		{
			auto word_ptr = &it->second;
			auto& w = *word_ptr;
			LOG_DEBUG("word: " << w.get_value());
			if (i > 10)
				continue;
			auto word_button = create<button>();
			word_button->set_text(w.get_value());
			word_button->set_on_click([self = this, &w](bool up) {
				auto dialog = self->app().menu_manager().current_menu().create<utils::ui::dialog>();
				dialog->set_horizontal_alignment(utils::ui::widget::alignment::center);
				dialog->set_vertical_alignment(utils::ui::widget::alignment::center);
				dialog->set_title(w.get_value());
				dialog->set_size_policy(widget::size_policy::type::automatic, widget::size_policy::type::automatic);
				// TODO: use modal after supporting displaying modals on top of other modals
				// dialog->set_modal(true);
				auto word_input = self->create<text_input>(dialog.get());
				word_input->set_value(w.get_value());
				auto example_input = self->create<text_input>(dialog.get());
				example_input->set_value(w.get_example());
				auto translation_input = self->create<text_input>(dialog.get());
				translation_input->set_value(w.get_translation());
				auto store_button = self->create<button>(dialog.get());
				store_button->set_text("Store");
				store_button->set_enable_if([example_input, translation_input, word_input, &w]() {
					return w.get_example() != example_input->get_value() || w.get_translation() != translation_input->get_value() || w.get_value() != word_input->get_value();
				});
				store_button->set_on_click([self = self, &w, example_input, translation_input, word_input](bool up) {
					w.set_example(example_input->get_value());
					w.set_translation(translation_input->get_value());
					if (!w.set_value(word_input->get_value()))
					{
						self->app().show_message("Word '" + word_input->get_value() + "' already exists.");
						return;
					}
					if (g_words.update_local_storage() == 0)
						self->app().show_message("Word stored successfully");
					else
						self->app().show_message("Failed to store the word");
				});
				auto delete_button = self->create<button>(dialog.get());
				delete_button->set_text("Delete");
				delete_button->set_on_click([self, &w](bool up) {
					self->app().ask_user("Are you sure you want to delete the word '" + w.get_value() + "'?", [self, &w](bool yes) {
						if (yes)
						{
							g_words.list.erase(w.get_value());
							if (g_words.update_local_storage() == 0)
								self->app().show_message("Word '" + w.get_value() + "' deleted successfully");
							else
								self->app().show_message("Failed to delete the word");
							self->close();
						}
					});
				});
				// The buttons are added automatically through the create() method (when no parent is passed, it takes this as parent)
				// The dialog is shown automatically when it's created
				auto close_button = self->create<button>(dialog.get());
				close_button->set_text("Close");
				close_button->set_on_click([dialog_ptr = dialog.get()](bool up) {
					dialog_ptr->close();
				});
			});
			word_button->add_on_update([word_button, i, &w](float dt) {
				if (w.get_value() != word_button->get_text())
					word_button->set_text(w.get_value());
				return true;
			});
		}
		return 0;
	}
}
