#pragma once

#include<SDL.h>
#include<SDL_mixer.h>

#include<iostream>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "Scene.h"
#include "core.h"
#include "DrawKolam.h"


class PopUpMenu : public Scene
{
	bool Init() override;
	void Update() override;
	void Render() override;
	void HandleEvent(SDL_Event* e) override;
};





