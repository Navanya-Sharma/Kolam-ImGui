#pragma once
#include <SDL.h>

//CLASSES

class Scene {
	public:
		virtual bool Init()=0;
		virtual void Update()=0;
		virtual void Render() = 0;

};

class SceneManager{
public:
	SceneManager() {
		currentScene = nullptr;
	}
	bool ChangeScene(std::unique_ptr<Scene> newScene);
	void Update();
	void Render();

private:
	std::unique_ptr<Scene> currentScene =nullptr;
};

//DECLARATION

//SDL
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SceneManager gSceneManager;


//ImGUI
extern ImGuiIO* io;
extern ImFont* gFont;
extern ImFont* BoldFont;
extern ImGuiStyle* style;

//Rest
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;


//FUNCTION DECLARATION
bool init();
bool initImGui();
bool load();

void close();

