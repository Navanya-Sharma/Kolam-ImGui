#pragma once
#include<SDL.h>

#include "KolamButtons.h"
#include "Scene.h"
#include "core.h"

class DrawKolam : public Scene
{
public:	
	
	bool Init() override;
	void Update() override;
	void Render() override;
	void HandleEvent(SDL_Event *e) override;
	//int CheckInside();
	//int ActiveButtonID();
};

void DrawButtons();
void RenderButtons();
void GlobalDec();

int ActiveButtonID(buttonType &place);
int CheckInside(buttonType &place);

void ClearAll();

bool InitImGui();
bool InitTextures();

extern ImVec4 BGcolor; 
extern ImVec4 FRcolor;


