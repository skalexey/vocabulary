#pragma once

#include <memory>
#include <optional>
#include <utils/terminator.h>
#include <abstract_ui/app.h>
#include <abstract_ui/helpers/user_input.h>
#include <utils/filesystem.h>
#include <utils/common.h>
#include <DMBCore.h>
#include "ui/controllers/play_random_word_controller.h"
#include "ui/controllers/new_word_controller.h"
namespace vocabulary_core
{
	class app : public virtual utils::ui::app, public utils::ui::user_input
	{
		using base = utils::ui::app;

	public:
		app(int argc, char* argv[]);
		void request_auth(const std::string& user_name, const std::string& token, const utils::void_int_cb& on_result);

		play_random_word_controller& get_play_random_word_controller() {
			return *m_window_ctrl;
		}
		
		void upload_changes(const utils::void_int_cb& cb = nullptr, bool force = false); // Keep "force" the last argument for safety
		
	protected:
		int init() override;

	private:
		void init_words(const utils::void_int_cb& on_result);
		void load_words();
		void sync_resources(const utils::void_int_cb& cb = nullptr);
		void upload_changes_job();
		void update_words_dir(const std::string& new_dir);
		using opt_path_t = std::optional<fs::path>;
		using on_path_selected_t = std::function<void(const opt_path_t&)>;
		void ask_directory(const std::string& msg, const fs::path& path, const on_path_selected_t& callback);
		void ask_file(const std::string& msg, const fs::path& path, const on_path_selected_t& callback);
		void choose_directory(const on_path_selected_t& callback, const std::string& default_path);
		void on_path_selected(const opt_path_t& path, const on_path_selected_t& on_result);

	protected:
		void set_offline_mode(bool offline) {
			m_is_offline = offline;
		}

		bool is_offline_mode() const {
			return m_is_offline;
		}

		void register_menus();

	private:
		play_random_word_controller_ptr m_window_ctrl;
		new_word_controller_ptr m_new_word_ctrl;
		dmb::Model m_cfg_model;
		bool m_is_offline = false;
		std::unique_ptr<utils::terminator> m_terminator;
	};
}
