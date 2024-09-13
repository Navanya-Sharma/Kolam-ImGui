#pragma once
#include "common.h"

//CLASSES

class Scene {
	public:
		virtual bool Init()=0;
		virtual void Update()=0;
		virtual void Render() = 0;
		virtual void HandleEvent(SDL_Event *e) = 0;

};

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

