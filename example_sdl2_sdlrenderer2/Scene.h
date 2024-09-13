#pragma once

#include <SDL.h>

class Scene {
public:
	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void HandleEvent(SDL_Event* e) = 0;

};