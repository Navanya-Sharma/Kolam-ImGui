#pragma once
#include "common.h"

class PopUpMenu : public Scene
{
	bool Init() override;
	void Update() override;
	void Render() override;
	void HandleEvent(SDL_Event* e) override;
};





