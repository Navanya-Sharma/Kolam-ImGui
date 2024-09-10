#pragma once
#include <SDL.h>
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

bool init();
bool load();

void close();