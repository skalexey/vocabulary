#pragma once

#include <memory>
#include <stdio.h>
#include <csignal>
#include <string>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/io_utils.h>
#include <utils/networking/uploader_with_auth.h>
#include <utils/dmb/auth_async.h>
#include <utils/networking/sync_resources.h>
#include <utils/datetime.h>
#include <utils/print_defs.h>
#include <utils/common.h>
#include <utils/Log.h>
#include <abstract_ui/widget_factory.h>
#include <abstract_ui/widgets/dialogs/dialog_with_buttons.h>
#include <http/http_client.h>
#include <http/uploader.h>
#include <http/authenticator.h>
#include "words.h"
#include "ui/controllers/play_random_word_controller.h"
#include "app.h"

LOG_POSTFIX("\n");
LOG_PREFIX("[vocabulary_core::app]: ");

words g_words;
vocabulary_core::app* g_app = nullptr;

using utils::void_int_cb;

// Used in utils/networking/sync_resources.h
void ask_user(
    const std::string& question
    , const utils::void_bool_cb& on_answer
    , const char* yes_btn_text_ptr
    , const char* no_btn_text_ptr
)
{
	if (g_app)
		g_app->ask_user(question, on_answer, yes_btn_text_ptr, no_btn_text_ptr);
}

void ask_line(
	const std::string& msg
	, const utils::void_string_bool_cb& on_answer
	, const std::string& default_value
	, const char* ok_btn_text
	, const char* cancel_btn_text
)
{
    if (g_app)
        g_app->ask_line(msg, on_answer, default_value, ok_btn_text, cancel_btn_text);
}

void request_auth(
	const std::string& user_name
	, const std::string& token
	, const utils::void_int_cb& on_result
)
{
	if (g_app)
		g_app->request_auth(user_name, token, on_result);
}

namespace
{
	fs::path g_words_fpath;
	fs::path identity_path;
    fs::path cfg_path;
    fs::path def_cfg_path;
	
	utils::networking::resources_list g_resources_list;
	extern std::unique_ptr<dmb::Model> identity_model_ptr;

	std::ofstream words_fo;
	std::ifstream words_fi;

	const std::string host = "srv.vllibrary.net";
	const int port = 443;
	anp::tcp::endpoint_t g_ep = { host, port };

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
}

// Declarations
int upload_words();
int init_words();
auto load_words();
auto backup_words();
int upload_file(const fs::path& fpath);


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

namespace vocabulary_core
{
// App Definitions
	app::app(int argc, char* argv[])
		: base(argc, argv)
		, utils::ui::user_input(this)
	{}

	void app::request_auth(const std::string& user_name, const std::string& token, const utils::void_int_cb& on_result)
	{
		using namespace anp;
		authenticator_ptr a = std::make_shared<authenticator>();
		a->auth_async({ host, port }, "/v/a.php", { user_name, token }, [a, on_result](int result) {
			on_result(result);
		});
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
		app::ask_line(
			"Enter words location directory or file path"
			, [=](const std::string& path, bool cancelled) {
				callback(cancelled ? opt_path_t{} : opt_path_t(path));
			}
			, default_path
		);
	}

	void app::on_path_selected(const opt_path_t& path, const on_path_selected_t& on_result)
	{
		if (path.has_value())
		{
			auto& path_val = path.value();
			if (utils::file::exists(path_val))
			{
				if (fs::is_directory(path_val))
				{
					auto words_path = get_words_path(path.value());
					on_path_selected(words_path, on_result);
					return;
				}
				// If the file exists
				if (on_result)
					on_result(path);
			}
			else
			{
				if (utils::file::is_file_path(path_val))
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
							, [self = this, on_result](const opt_path_t& path) {
								self->on_path_selected(path, on_result);
							}
						);
					return;
				}
				else
				{
					ask_directory(
						(path_val.empty() ? "There is no such directory '" + path_val.string() + "'. " : std::string()) + "Please, choose one of the following options."
						, path_val
						, [=](const opt_path_t& path) {
							on_path_selected(path, on_result);
						}
					);
				}
			}
		}
		else
		{
			MSG("Haven't got an answer from the user for words directory location");
			on_result({});
		}
	}

	void app::ask_directory(const std::string &msg, const fs::path &path, const on_path_selected_t& callback)
	{
		auto d = get_factory().create<utils::ui::dialog_with_buttons>(this).get();
		utils::ui::dialog_with_buttons::actions_t actions = {
			{
				"Choose another path"
				, [self = this, callback, path, d] (bool up) {
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
		d->show();
	}

	void app::ask_file(const std::string &msg, const fs::path& path, const on_path_selected_t& callback)
	{
		auto d = get_factory().create<utils::ui::dialog_with_buttons>(this).get();
		// d is alive until it is closed
		utils::ui::dialog_with_buttons::actions_t actions = {
			{
				"Create"
				, [=](bool up) {
					utils::file::create(path);
					callback(get_words_path(path));
					d->close();
				}
			},
			{
				"Choose another path"
				, [self = this, callback, path, d](bool up) {
					self->choose_directory(callback, path.string());
					d->close();
				}
			}
		};

		if (fs::canonical(path.parent_path()) != fs::canonical(utils::file::temp_directory_path().parent_path()))
		{
			actions.push_back({
				"Default (create a file in temp directory)"
				, [=](bool up) {
					auto new_path = utils::file::temp_directory_path() / words_fname_default;
					utils::file::create(new_path);
					callback(get_words_path(new_path));
					d->close();
				}
			});
		}

		d->set_message(msg);
		d->setup_buttons(actions);
		d->show();	
	}

	void app::init_words(const void_int_cb& on_result)
	{
		LOG("init_words()");

		if (!m_cfg_model.Load(cfg_path.string()))
			m_cfg_model.Store(cfg_path.string(), { true });

		auto on_selected_result = [self = this, on_result](const opt_path_t& path) {
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

	int app::init()
	{
		using namespace anp;

		LOG("init()");

		identity_path = utils::file::temp_directory_path() / "vocabulary_identity.json";
		cfg_path = utils::file::temp_directory_path() / "vocabulary_config.json";
		def_cfg_path = utils::file::temp_directory_path() / "vocabulary_config_default.json";

		g_app = this;

		std::signal(SIGINT, [] (int sig) {
			LOG_DEBUG("SIGINT raised");
			// TODO: maybe not to do it?
			if (g_app) // Because we can't capture anything in the lambda for std::signal
				g_app->sync_resources();
			// TODO: pause?
			g_app = nullptr;
		});

		// Auto uploader on program finish
		m_terminator = std::make_unique<utils::terminator>([this] {
			LOG_DEBUG("Terminating...");
			// TODO: maybe not to do it?
			sync_resources();
			// TODO: pause?
		});
		
		try
		{
			m_window_ctrl = std::make_unique<play_random_word_controller>(*this);
			m_window_ctrl->show();
		}
		catch (std::exception& ex)
		{
			LOG("Creating controller exception: " << ex.what());
		}
		catch (...)
		{
			LOG("Creating controller exception!");
		}

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

		get_identity([self = this, after_auth](bool ok, std::string, std::string) {
			if (!ok)
			{
				MSG("No login information has been provided. Exit.");
				return;
			}

			auth([=](int result) {
				if (result == 0)
				{
					self->show_message(STR("Hello, " << identity_model_ptr->GetContent().GetData()["user"]["name"].AsString().Val() << "!"));
					after_auth();
				}
				else
				{
					utils::file::remove(identity_path);
					identity_model_ptr.reset(nullptr);
					self->app::ask_user("Authentication error. Continue in offline mode?", [=](bool yes) {
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

	bool app::core_update(float dt)
	{
		if (!m_window_ctrl->update(dt))
			return false;
		return on_core_update(dt);
	}

	bool app::on_update(float dt) {
		if (!base::update(dt))
			return false;
		return core_update(dt);
	}
}