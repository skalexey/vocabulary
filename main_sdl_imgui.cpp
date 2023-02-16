// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// Important to understand: SDL_Renderer is an _optional_ component of SDL. We do not recommend you use SDL_Renderer
// because it provide a rather limited API to the end-user. We provide this backend for the sake of completeness.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.

#include <stdio.h>
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <utils/Log.h>
#include <utils/file_utils.h>
#include <utils/string_utils.h>
#include <utils/io_utils.h>
#include <utils/dmb/auth.h>
#include <http/http_client.h>
#include <http/uploader.h>
#include <http/authenticator.h>

LOG_POSTFIX("\n");
LOG_PREFIX("[main]: ");

#define COUT(msg1) std::cout << msg1
#define MSG(msg1) COUT(msg1 << '\n')

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

namespace
{
	fs::path g_words_fpath;
	const fs::path identity_path = fs::temp_directory_path() / "vocabulary_identity.json";
    const fs::path cfg_path = fs::temp_directory_path() / "vocabulary_config.json";
    const fs::path def_cfg_path = fs::temp_directory_path() / "vocabulary_config_default.json";

	std::unique_ptr<dmb::Model> identity_model_ptr;

	std::ofstream words_fo;
	std::ifstream words_fi;

    std::string g_words;

	const std::string host = "skalexey.ru";
	const int port = 80;
}

int init_words()
{
	const std::string words_fname = "Words tmp.txt";

    utils::input::register_command("~skip");

	dmb::Model cfg_model;
	if (!cfg_model.Load(cfg_path.string()))
		cfg_model.Store(cfg_path.string(), { true });

	LOG("init_words()");

	const std::string words_location_field_name = "words_location";

	auto update_words_dir = [&](const std::string& new_dir)
	{
		auto& data = cfg_model.GetContent().GetData();
		if (fs::path(new_dir) == fs::temp_directory_path())
			data.Set(words_location_field_name, "");
		else
		{
			if (data.Get(words_location_field_name).AsString().Val() != new_dir)
			{
				data.Set(words_location_field_name, new_dir);
				cfg_model.Store(cfg_path.string(), { true });
			}
		}
	};

    auto& words_location_var = cfg_model.GetContent().Get(words_location_field_name).AsString();
	auto words_location = words_location_var.Val();
	fs::path words_path = words_location.empty() ? fs::temp_directory_path() : fs::path(words_location);
	if (!words_path.has_filename())
		words_path /= words_fname;
	bool already_created = utils::file::exists(words_path);
	while (!already_created)
	{
		std::string msg1, msg2;
		if (!words_location.empty())
		{
			msg1 = "Can't find words in the directory provided by you: '"
				+ words_location + "'. Would you like to provide a custom path? "
				"Otherwise an empty file will be created in the current directory.";
			msg2 = "Enter words location directory or type 'skip' to use the "
				"current directory or 'exit' to close the application";
		}
		else
		{
			msg1 = "Where are your words located?\nWould you like to specify a custom path? "
				"Otherwise we will keep it in the app data directory located here:\n"
				+ fs::temp_directory_path().string();
			msg2 = "Enter words location directory or type 'skip' to use the "
				"default folder or 'exit' to close the application";
		}
		if (utils::input::ask_user(msg1))
		{
			fs::path entered_path;
			do
			{
				COUT(msg2 << "\n > ");
				std::string words_dir;

				while (words_dir.empty() && utils::input::last_getline_valid)
				{
					if (!utils::input::getline(std::cin, words_dir))
					{
						LOG_ERROR("Input stream failure");
						return 4; // 4
					}
                    // words_dir = "C:\\English";
				}

				if (!utils::input::last_getline_valid)
				{
					if (utils::input::last_command == "~exit")
						return 0;
					else if (utils::input::last_command == "~skip")
						break;
				}
				auto p = fs::path(words_dir);
				if (!utils::file::dir_exists(p))
				{
					if (utils::input::ask_user("There is no directory in the provided path. "
						"Would you use temporary directory instead? "
						"It is located here:\n" + fs::temp_directory_path().string())
						)
					{
						entered_path = fs::temp_directory_path();
						words_dir = "";
					}
				}
				else
					words_dir = (entered_path = p).string();
			} while (entered_path.empty());
			words_path = entered_path / words_fname;
            words_location_var = words_path.parent_path().string();
            cfg_model.Store(cfg_path.string(), { true });
			// Load or create DB
				//MSG("Sorry, but without a spellbook you can't cast any spell. Come back when you are ready.");
		}
		update_words_dir(words_location);
		if (!utils::file::exists(cfg_path))
		{
			if (auto erc = utils::file::copy_file(def_cfg_path, cfg_path))
			{	// No default config found
				if (erc == 3)
				{
					MSG("Can't create config in the location '" << cfg_path <<
						"'. Reason: '" << utils::file::last_error() << "'"
					);
				}
				else
					MSG("Unexpected error (code " << (erc *= 10) << ")");
				return erc;
			}
		}
		already_created = true;
		MSG("Your words file is created at the path '" << fs::absolute(words_path).string() << "'");
	}
    g_words_fpath = words_path;
    return 0;
}


bool request_auth(const std::string& user_name, const std::string& token)
{
    using namespace anp;
    authenticator a;
    return a.auth({host, port}, "/v/a.php", {user_name, token}) == http_client::erc::no_error;
}

void ShowRandomWord()
{
    LOG("ShowRandomWord");
}

void ShowCorrect()
{
    LOG("Answer is correct");
}

void ShowWrong()
{
    LOG("Answer is wrong");
}

bool UploadWords()
{
    LOG("UploadWords");
    vl::Object& data = identity_model_ptr->GetContent().GetData();
	std::string user_name, token;
	if (!get_identity(&user_name, &token))
		return false;
    using namespace anp;
    uploader u;
    u.upload_file({host, port}, g_words_fpath.string(), {user_name, token}, "/v/h.php");
    return true;
}

void Answer(const char* answer)
{
    LOG("Answer: " << answer);
    // Send answer to server
    using namespace anp;
	http_client c;
	bool success = false;
	std::string response;
    std::string host = "skalexey.ru";
    int port = 80;
    auto name = get_user_name();
	auto token = get_user_token();
	c.query({host, port}, "GET"
		, utils::format_str("/v/play.php?u=%s&t=%s", name.c_str(), token.c_str()).c_str()
		, [=, &success, &response, &c](
            const headers_t&
			, const char* data
			, std::size_t sz
			, int code
		) -> bool
		{
			LOG_VERBOSE("\nReceived " << sz << " bytes:");
			std::string s(data, data + sz);
			LOG_VERBOSE(s);
			response.insert(response.end(), data, data + sz);
			if (s.find("Correct") != std::string::npos)
				success = true;
			c.notify(http_client::erc::no_error);
			return true;
		}
	);
    if (success)
        ShowCorrect();
    else
        ShowWrong();
}

// Main code
int main(int, char**)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    
    init_words();
    UploadWords();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Vocabulary", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    // Setup SDL_Renderer instance
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return -2;
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();

        if (ImGui::Button("Random word"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            ShowRandomWord();

        static char str0[128] = "";
        ImGui::InputText("input_answer", str0, IM_ARRAYSIZE(str0));
        if (ImGui::Button("Answer"))
            Answer(str0);

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
