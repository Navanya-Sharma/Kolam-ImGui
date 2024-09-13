#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
#include<iostream> 
#include <memory>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "Scene.h""

//CLASSES



class SceneManager{
public:
	SceneManager() {
		currentScene = nullptr;
	}
	bool ChangeScene(std::unique_ptr<Scene> newScene) {
		if (currentScene != nullptr)
			currentScene->~Scene();
		currentScene = std::move(newScene);
		return currentScene->Init();
	}
	void Update() {
		if (currentScene != nullptr)
			currentScene->Update();
	}
	void Render() {
		if (currentScene != nullptr)
			currentScene->Render();
	}
	void HandleEvent(SDL_Event *e) {
		if (currentScene != nullptr)
			currentScene->HandleEvent(e);
	}

private:
	std::unique_ptr<Scene> currentScene =nullptr;
};

//DECLARATION

//SDL
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Rect ImgUD[2], ImgLR[2];
extern Mix_Music* music;
extern Mix_Chunk* buttSound;

//ImGUI
extern ImGuiIO* io;
extern ImFont* gFont;
extern ImFont* BoldFont;
extern ImGuiStyle* style;

//CLASSES INITIALIZED
extern SceneManager gSceneManager;

//Rest
extern const int SCREEN_WIDTH, SCREEN_HEIGHT;
extern int SPACE, ROWS, COLS, OffsetX, OffsetY, TOTAL_BUTTONS, MaxTHICK;
extern float THICK;


//FUNCTION DECLARATION
bool init();
bool initImGui();
void close();

