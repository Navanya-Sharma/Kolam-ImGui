#pragma once
#include "common.h"



class DrawKolam : public Scene
{
public:	
	enum buttonType {
		top,
		right,
		bottom,
		left,
	};
	bool Init() override;
	void Update() override;
	void Render() override;
	void HandleEvent(SDL_Event *e) override;
	//int CheckInside();
	//int ActiveButtonID();

private:
	int pev;
	int i;
	buttonType place;
};

void DrawButtons();
void GlobalDec();

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);
int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);

bool MakeDot();
bool MakeSheetLR();
bool MakeSheetUD();

int ActiveButtonID(DrawKolam::buttonType &place);

int CheckInside(DrawKolam::buttonType &place);


