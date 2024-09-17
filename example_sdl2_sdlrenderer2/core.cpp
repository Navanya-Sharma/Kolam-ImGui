
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>

#include "core.h"
#include "Scene.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SceneManager gSceneManager;

SDL_Rect ImgUD[2], ImgLR[2];
Mix_Music* music=NULL;
Mix_Chunk* buttSound=NULL;

ImGuiIO* io = NULL;
ImFont* gFont = NULL;
ImFont* BoldFont = NULL;
ImGuiStyle* style = NULL;

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 600;
int SPACE, ROWS, COLS, OffsetX, OffsetY, TOTAL_BUTTONS, MaxTHICK;
float THICK;
char * NAME ="My Digital Kolam";


bool init() {
	bool pass = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
		printf("SDL Not initialized. Error %s\n", SDL_GetError());
		pass = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		#ifdef SDL_HINT_IME_SHOW_UI
				SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		#endif
		
		SDL_WindowFlags window_flags = (SDL_WindowFlags)
			(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

		gWindow = SDL_CreateWindow("Kolam", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
		if (gWindow == NULL) {
			printf("Failed to create Window.Erorr %s", SDL_GetError());
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				pass = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					pass = false;
				}
			}
		}


		/*if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			pass = false;
		}*/

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			pass = false;
		}
		else
		{
			music = Mix_LoadMUS("Music/santoor.mp3");
			if (music == NULL)
			{
				printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
				pass = false;
			}
			buttSound = Mix_LoadWAV("Music/low.wav");
			if (buttSound == NULL)
			{
				printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
				pass = false;
			}
		}

		ImGui::CreateContext();
		//gSceneManager->SceneManager();
	}

	return pass;
}

bool initImGui() {
	bool pass = true;
	io = &ImGui::GetIO(); (void)io;

	if (!io) { printf("IO not loaded");pass = false; }

	else {
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io->ConfigDebugIsDebuggerPresent = true;
		
		gFont = io->Fonts->AddFontFromFileTTF("Font/roboto/Roboto-Regular.ttf", 30);
		
		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 30.0f;
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		io->Fonts->AddFontFromFileTTF("Font/fontawesome/webfonts/fa-solid-900.ttf", 30.0f, & config,icon_ranges);
		
		BoldFont = io->Fonts->AddFontFromFileTTF("Font/roboto/Roboto-Bold.ttf", 45);
		io->Fonts->AddFontDefault();

		if (!gFont) { printf("gFont not loaded. Regular Font");pass = false; }
		if (!BoldFont) { printf("BoldFont not loaded");pass = false; }
		
	}

	ImGui_ImplSDL2_InitForSDLRenderer(gWindow, gRenderer);
	ImGui_ImplSDLRenderer2_Init(gRenderer);

	return pass;
}






