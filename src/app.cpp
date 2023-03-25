#pragma once

#include <memory>
#include <stdio.h>
#include <csignal>
#include <SDL.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/io_utils.h>
#include <utils/networking/uploader_with_auth.h>
#include <utils/dmb/auth_async.h>
#include <utils/networking/sync_resources.h>
#include <utils/ui/imgui/widgets/dialogs/dialog_yes_no.h>
#include <utils/ui/imgui/widgets/dialogs/dialog_with_buttons.h>
#include <utils/datetime.h>
#include <utils/print_defs.h>
#include <utils/common.h>
#include <utils/Log.h>
#include <http/http_client.h>
#include <http/uploader.h>
#include <http/authenticator.h>
#include "words.h"
#include "ui/controllers/play_random_word_controller.h"
#include "app.h"

LOG_POSTFIX("\n");
LOG_PREFIX("[app]: ");

words g_words;
extern app* g_app;

using utils::ui::imgui::dialog_with_buttons;
using utils::void_int_cb;

namespace
{
	fs::path g_words_fpath;
	fs::path identity_path;
    fs::path cfg_path;
    fs::path def_cfg_path;
	
	const std::string log_fname = "vocabulary_log.txt";

	utils::networking::resources_list g_resources_list;
	extern std::unique_ptr<dmb::Model> identity_model_ptr;

	std::ofstream words_fo;
	std::ifstream words_fi;

	const std::string host = "skalexey.ru";
	const int port = 80;
	anp::endpoint_t g_ep = { host, port };

	const std::string words_location_field_name = "words_location";
	const std::string words_fname_default = "words.txt";

	auto msg1_with_dir(const std::string& dir)
	{
		return "Can't find words in the directory provided by you: '"
			+ dir + "'. Would you like to provide a custom path? "
			"Otherwise an empty file will be created in the current directory.";
	};
	auto msg1_with_file(const std::string& file)
	{
		return "Can't find words in the file provided by you: '"
			+ file + "'. Would you like to provide a custom path? "
			"Otherwise an empty file will be created in the current directory.";
	};

	const auto msg2_default = "Enter words file location or a directory or type 'skip' to use the "
				"default folder or 'exit' to close the application";

	const auto msg2_current = "Enter words file location or a directory or type 'skip' to use the "
				"current directory or 'exit' to close the application";

	const ImVec4 m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

// Declarations
int upload_words();
int init_words();
auto load_words();
auto backup_words();
int upload_file(const fs::path& fpath);


// Definitions

app::app() 
	: utils::ui::user_input(this)
{
	set_resolution(1280, 720);
	// Create a new log file
	std::ofstream f(utils::file::temp_directory_path() / log_fname);
}

int upload_file(const fs::path& fpath)
{
	LOG_DEBUG("upload_file(" << fpath.string() << ")");
	return upload_file(fpath.string(), g_ep, "/v/h.php");
}

auto backup_words()
{
	auto cur_dt = utils::current_datetime("%02i-%02i-%02i-%03li");
	auto new_fpath = fs::path(g_words_fpath.parent_path() / fs::path(utils::format_str("words-%s.txt", cur_dt.c_str())));
	utils::file::copy(g_words_fpath, new_fpath);
	upload_file(new_fpath);
	return false;
};

int upload_words()
{
    return upload_file(g_words_fpath);
}

auto get_words_path(const fs::path& path)
{
	fs::path words_path = path.empty() ? utils::file::temp_directory_path() : path;
    if (utils::file::exists(words_path))
	{
		if (utils::file::is_directory(words_path))
			words_path /= words_fname_default;
	}
	else
		if (!utils::file::is_file_path(words_path))
			words_path /= words_fname_default;
	return words_path;
};

auto get_words_path_by_string(const std::string& path_str)
{
	return get_words_path(fs::path(path_str));
}

// App Definitions
void app::request_auth(const std::string& user_name, const std::string& token, const utils::void_int_cb& on_result)
{
	using namespace anp;
	authenticator_ptr a = std::make_shared<authenticator>();
	a->auth_async({ host, port }, "/v/a.php", { user_name, token }, [a, on_result](int result) {
		on_result(result);
	});
}

SDL_Window* app::create_window()
{
	auto& r = get_resolution();
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	return SDL_CreateWindow("Vocabulary", 30, 30, r.x, r.y, window_flags);
}

void app::load_words()
{
	LOG("load_words()");
	g_words.load(g_words_fpath);
	m_window_ctrl->show_random_word();
}

void app::update_words_dir(const std::string& new_dir)
{
	auto& content_data = m_cfg_model.GetContent().GetData();
	if (fs::path(new_dir) == utils::file::temp_directory_path())
		content_data.Set(words_location_field_name, "");
	else
	{
		if (content_data.Get(words_location_field_name).AsString().Val() != new_dir)
		{
			content_data.Set(words_location_field_name, new_dir);
			m_cfg_model.Store(cfg_path.string(), { true });
		}
	}
}
void app::choose_directory(const on_path_selected_t &callback, const std::string& default_path)
{
	ask_line(
		"Enter words location directory or file path"
		, [=](const std::string& path, bool cancelled) {
			callback(cancelled ? opt_path_t(path) : opt_path_t{});
		}
		, default_path
	);
}

void app::on_path_selected(const opt_path_t& path, const on_path_selected_t& on_result)
{
	if (path.has_value())
	{
		auto& path_val = path.value();
		if (utils::file::is_file_path(path_val))
		{
			if (!utils::file::exists(path_val))
			{
				if (!utils::file::exists(path_val.parent_path()))
					ask_directory(
						(path_val.empty() ? "There is no such directory '" + path_val.string() + "'. " : std::string()) + "Please, choose one of the following options."
						, path_val
						, [=](const opt_path_t& path) {
							on_path_selected(path, on_result);
						}
					);
				else
					ask_file(
						"Can't find words storage file '" + path_val.string() + "'. Please, enter the path or provide another directory."
						, path_val
						, [=, self = this](const opt_path_t& path) {
							self->on_path_selected(path, on_result);
						}
					);
				return;
			}
		}
		else
		{
			if (!utils::file::exists(path_val))
				ask_directory(
					(path_val.empty() ? "There is no such directory '" + path_val.string() + "'. " : std::string()) + "Please, choose one of the following options."
					, path_val
					, [=](const opt_path_t& path) {
						on_path_selected(path, on_result);
					}
				);
			else
			{
				auto words_path = get_words_path(path.value());
				on_path_selected(words_path, on_result);
			}
			return;
		}
		if (on_result)
			on_result(path);
	}
	else
	{
		MSG("Haven't got an answer from the user for words directory location");
		on_result({});
	}
}

void app::ask_directory(const std::string &msg, const fs::path &path, const on_path_selected_t& callback)
{
	auto d = std::make_shared<dialog_with_buttons>();
	dialog_with_buttons::actions_t actions = {
		{
			"Choose another path"
			, [=, self = this] (bool up) {
				self->choose_directory(callback, path.string());
				d->close();
			}
		}
		, {
			"Default (use system temporary directory)"
			, [=] (bool up) {
				callback(get_words_path(utils::file::temp_directory_path()));
				d->close();
			}
		}
	};
	d->setup_buttons(actions);
	d->set_message(msg);
	add_on_update([=](float dt) {
		return d->show();
	});
}

void app::ask_file(const std::string &msg, const fs::path& path, const on_path_selected_t& callback)
{
	auto d = std::make_shared<dialog_with_buttons>();
	dialog_with_buttons::actions_t actions = {
		{
			"Choose another path"
			, [=, self = this](bool up) {
				self->choose_directory(callback, path.string());
				d->close();
			}
		}
		, {
			"Default (create a file in temp directory)"
			, [=](bool up) {
				callback(get_words_path(utils::file::temp_directory_path() / words_fname_default));
				d->close();
			}
		}
		, {
			"Create"
			, [=](bool up) {
				utils::file::create(path);
				callback(get_words_path(path));
				d->close();
			}
		}
	};

	d->set_message(msg);
	d->setup_buttons(actions);
	
	add_on_update([=](float dt) {
		return d->show();
	});
}

void app::init_words(const void_int_cb& on_result)
{
	LOG("init_words()");

	if (!m_cfg_model.Load(cfg_path.string()))
		m_cfg_model.Store(cfg_path.string(), { true });

	auto on_selected_result = [=, self = this](const opt_path_t& path) {
		auto path_val = path.value();
		self->update_words_dir(path_val.string());
		g_words_fpath = path_val;
		g_resources_list = {
			{ "words.txt", g_words_fpath }
		};
		on_result(0);
	};

    auto& words_location_var = m_cfg_model.GetContent().Get(words_location_field_name).AsString();

	auto words_path = get_words_path_by_string(words_location_var.Val());
	
	on_path_selected(words_path, on_selected_result);
}

void app::sync_resources(const void_int_cb& cb)
{
	LOG("sync_resources()");
	return utils::networking::sync_resources(g_ep, "/v/s.php", "/v/h.php", g_resources_list
		, [=](int code) {
			if (code == 0)
				load_words();
			else
				show_message("sync_resources() failed with error code: " + std::to_string(code));
			if (cb)
				cb(code);
		});
}

int app::init() {
	using namespace anp;

	std::cout.rdbuf(m_log_stream.rdbuf());
	
    LOG("init()");

	identity_path = utils::file::temp_directory_path() / "vocabulary_identity.json";
	cfg_path = utils::file::temp_directory_path() / "vocabulary_config.json";
	def_cfg_path = utils::file::temp_directory_path() / "vocabulary_config_default.json";

	std::signal(SIGINT, [] (int sig) {
		LOG_DEBUG("SIGINT raised");
		// TODO: maybe not to do it?
		if (g_app) // Because we can't capture anything in the lambda for std::signal
			g_app->sync_resources();
		// TODO: pause?
	});

	// Auto uploader on program finish
	m_terminator = std::make_unique<utils::terminator>([this] {
		LOG_DEBUG("Terminating...");
		// TODO: maybe not to do it?
		sync_resources();
		// TODO: pause?
	});
	
	m_window_ctrl = std::make_unique<play_random_word_controller>();

	auto after_auth = [self = this] () {
		self->init_words([=](int result_code) {
			//upload_words();

			if (self->is_offline_mode())
				return;

			self->sync_resources([=](int code) {
				if (code != 0)
					self->ask_user(
						"Errors while syncing resources. Continue in offline mode?"
						, [=](bool yes) {
							if (!yes)
								self->exit(100 * code);
							else
								self->set_offline_mode(true);
						}
					);
			});
		});
	};

	get_identity([=, self = this](bool ok, std::string, std::string) {
		if (!ok)
		{
			MSG("No login information has been provided. Exit.");
			return;
		}

		auth([=](int result) {
			if (result == 0)
			{
				show_message(STR("Hello, " << identity_model_ptr->GetContent().GetData()["user"]["name"].AsString().Val() << "!"));
				after_auth();
			}
			else
			{
				utils::file::remove(identity_path);
				identity_model_ptr.reset(nullptr);
				ask_user("Authentication error. Continue in offline mode?", [=](bool yes) {
					if (yes)
					{
						self->set_offline_mode(true);
						after_auth();
					}
					else
						self->exit(0);
				});
			}
		});
	});

	return 0;
}

bool app::on_update(float dt) {
	if (!m_log_stream.str().empty())
		m_log_stream.out();
	m_window_ctrl->show();
	auto& c = m_clear_color.z;
	return true;
}

void app::log_stringstream::out()
{
	if (str().empty())
		return;
	std::ofstream f(utils::file::temp_directory_path() / log_fname, std::ios::app);
	assert(f.is_open());
	f << str();
	SDL_Log("%s", str().c_str());
	str("");
	assert(str().empty());
}