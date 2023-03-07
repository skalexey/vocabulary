#pragma once

#include <memory>
#include <optional>
#include <utils/terminator.h>
#include <utils/ui/imgui/sdl_app.h>
#include <utils/ui/helpers/user_input.h>
#include <utils/filesystem.h>
#include <utils/common.h>
#include <DMBCore.h>
#include "ui/controllers/play_random_word_controller.h"

class app : public utils::ui::imgui::sdl_app, public utils::ui::user_input
{
public:
	app();
	bool on_update(float dt) override;

protected:
	int init() override;

private:
	void init_words(const utils::void_int_arg_cb& on_result);
	void load_words();
	void sync_resources(const utils::void_int_arg_cb& cb = nullptr);
	void update_words_dir(const std::string& new_dir);
	using opt_path_t = std::optional<fs::path>;
	using on_path_selected_t = std::function<void(const opt_path_t&)>;
	void ask_directory(const std::string& msg, const fs::path& path, const on_path_selected_t& callback);
	void ask_file(const std::string& msg, const fs::path& path, const on_path_selected_t& callback);
	void choose_directory(const on_path_selected_t& callback, const std::string& default_path);
	void on_path_selected(const opt_path_t& path, const on_path_selected_t& on_result);
	
protected:
	SDL_Window* create_window() override;

	void set_offline_mode(bool offline) {
		m_is_offline = offline;
	}

	bool is_offline_mode() const {
		return m_is_offline;
	}

private:
	play_random_word_controller_ptr m_window_ctrl;
	dmb::Model m_cfg_model;
	bool m_is_offline = false;
	std::unique_ptr<utils::terminator> m_terminator;
};

