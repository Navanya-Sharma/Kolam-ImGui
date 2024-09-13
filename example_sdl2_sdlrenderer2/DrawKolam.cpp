#include "common.h"



bool DrawKolam::Init() {	
	GlobalDec();
	pev = 0;i = 0;
	if (MakeDot() && MakeSheetLR() && MakeSheetUD())
	{
		SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0xFF);
		SDL_RenderClear(gRenderer);

		DrawButtons();
		return true;
	}
	else {
		printf("Textures not made");
		return false;
	}
	
	
}

void DrawKolam::Update() {
	
}

void DrawKolam::Render() {
	//SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(gRenderer);
	butts[pev].render();
	butts[i].render();
	pev = i;
}

void DrawKolam::HandleEvent(SDL_Event *e){
	//static int pev = 0, i = 0; 
	buttonType place;
	butts[pev].changeState(KolamButton::Outside);
	if (CheckInside(place)) {
		i = ActiveButtonID(place);
		butts[i].changeState(KolamButton::Inside);
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(-1, buttSound, 0);
			butts[i].changeSprite();
			butts[i].changeState(KolamButton::Pressed);
		}
		else if (e->type == SDL_MOUSEBUTTONUP) {
			butts[i].changeState(KolamButton::JustPressed);
		}
	}
}


void GlobalDec() {
	SPACE = std::min(SCREEN_WIDTH / (4 * ROWS), SCREEN_HEIGHT / (4 * COLS));
	OffsetX = (SCREEN_WIDTH - 4 * SPACE * ROWS) / 2;
	OffsetY = (SCREEN_HEIGHT - 4 * SPACE * ROWS) / 2;
	TOTAL_BUTTONS = 4 * ROWS * COLS;
	//butts = new KolamButton[TOTAL_BUTTONS];
	MaxTHICK = 1.172 * SPACE;// 2(2-root(2))*thick -> where the outer circle will touch the boundary
	THICK = 0.3 * SPACE;
}

void DrawButtons() {
	/*Freeing the existing buttons
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		butts[i].~KolamButton();
	}
	delete[] butts;
	butts = NULL;

	//Decl*/
	//KolamButton* butts;
	butts = new KolamButton[TOTAL_BUTTONS];

	int a = dot.GetWidth();

	for (int ri = 0, x = 2 * SPACE + OffsetX, i = 0; ri < COLS; ri++, x += 4 * SPACE) {
		for (int ci = 0, y = 2 * SPACE + OffsetY;ci < ROWS; ci++, i += 4, y += 4 * SPACE) {

			dot.Render(x - a / 2, y - a / 2);

			//0->left 1-> bottom 2-> right 3->top
			butts[i].setPosition(x - 2 * SPACE, y - SPACE, left);
			butts[i + 2].setPosition(x + SPACE - THICK, y - SPACE, right);
			butts[i + 1].setPosition(x - 2 * SPACE, y + SPACE, bottom);
			butts[i + 3].setPosition(x - 2 * SPACE, y - 2 * SPACE, top);
		}
	}
}

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;

	//CHECK_RENDERER_MAGIC(renderer, -1);

	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
	int offsetx, offsety, d;
	int status;

	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {

		status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
			x + offsety, y + offsetx);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
			x + offsetx, y + offsety);
		status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
			x + offsetx, y - offsety);
		status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
			x + offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}

bool MakeDot() {
	bool pass = true;
	
	if (!dot.CreateBlankSheet(SPACE / 3, SPACE / 3, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to make dot sprite\n");
		pass = false;
	}
	else {
		dot.SetAsRenderTarget();
		SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0XFF);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0xFF, 0xFF);

		SDL_RenderFillCircle(gRenderer, SPACE / 6, SPACE / 6, SPACE / 7);
		SDL_SetRenderTarget(gRenderer, NULL);

	}
	return pass;
}

bool MakeSheetUD() {
	bool pass = true;
	if (!sheetUD.CreateBlankSheet(SPACE * 4, SPACE * 2, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to load button sprite\n");
		pass = false;
	}
	else {
		sheetUD.SetAsRenderTarget();

		SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0XFF);
		SDL_RenderClear(gRenderer);
		float y;

		SDL_Rect rec = { 0,0,THICK,1 };
		//Draws the triangle
		SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0xFF, 0xFF);
		for (float x = SPACE;x < 2 * SPACE;x += 1) {
			y = -x + 2 * SPACE;
			rec.x = x - THICK / 2; rec.y = y;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		for (float x = 2 * SPACE;x < 3 * SPACE;x += 1) {
			y = x - 2 * SPACE;
			rec.x = x - THICK/ 2; rec.y = y;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		//Draws the circle
		SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0xFF, 0xFF);
		for (int x = -THICK * 0.3; x < 0.4 * THICK; x++) {
			SDL_RenderDrawCircle(gRenderer, 2 * SPACE, 3 * SPACE, (1.414 * SPACE) + x);
		}

		SDL_SetRenderTarget(gRenderer, NULL);

		ImgUD[0] = { 0,0, SPACE * 4, SPACE };
		ImgUD[1] = { 0, SPACE, SPACE * 4, SPACE };
	}
	return pass;
}

bool MakeSheetLR() {
	bool pass = true;
	if (!sheetLR.CreateBlankSheet(2 * (SPACE + THICK), 2 * SPACE, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to load button sprite\n");
		pass = false;
	}
	else {
		sheetLR.SetAsRenderTarget();

		SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0XFF);
		SDL_RenderClear(gRenderer);
		float y;
		SDL_Rect rec = { 0,0,1,THICK };

		//Draws lines
		SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0xFF, 0xFF);
		for (float x = sheetLR.GetWidth() / 2;x < sheetLR.GetWidth();x += 1) {
			y = -SPACE + x - 2 * THICK;
			rec.x = x; rec.y = y - THICK / 2;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		for (float x = sheetLR.GetWidth() / 2;x < sheetLR.GetWidth();x += 1) {
			y = 3 * SPACE - x + THICK * 2;
			rec.x = x; rec.y = y - THICK / 2;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		//Draws the circle
		SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0xFF, 0xFF);
		for (int x = -0.3 * THICK; x < 0.4 * THICK; x++) {
			SDL_RenderDrawCircle(gRenderer, -SPACE + THICK, SPACE, (1.414 * SPACE) + x);
		}

		SDL_SetRenderTarget(gRenderer, NULL);
		ImgLR[1] = { 0,0, sheetLR.GetWidth() / 2, sheetLR.GetHeight() };
		ImgLR[0] = { sheetLR.GetWidth() / 2,0, sheetLR.GetWidth() / 2, sheetLR.GetHeight() };
	}
	return pass;
}

int ActiveButtonID(buttonType &place) {
	int x, y, i;
	SDL_GetMouseState(&x, &y);
	int N = ROWS * ((x - OffsetX) / (4 * SPACE)) + ((y - OffsetY) / (4 * SPACE));
	switch (place)
	{
	case left:
		i = 4 * N;
		break;
	case bottom:
		i = 4 * N + 1;
		break;
	case right:
		i = 4 * N + 2;
		break;
	case top:
		i = 4 * N + 3;
		break;
	}
	return i;
}

int CheckInside(buttonType &place) {

	int x, y, xin, yin;
	int inn = 0;

	SDL_GetMouseState(&x, &y);

	if (x<OffsetX || x>(OffsetX + COLS * 4 * SPACE)) {
		return 0;
	}
	if (y<OffsetY || y>(OffsetX + ROWS * 4 * SPACE)) {
		return 0;
	}
	yin = (y - OffsetY - (4 * SPACE) * ((y - OffsetY) / (4 * SPACE))) / SPACE;

	if (yin == 0) {
		place = top;
		return 1;
	}
	else if (yin == 3) {
		place = bottom;
		return 1;
	}

	xin = (x - OffsetX - (4 * SPACE) * ((x - OffsetX) / (4 * SPACE)));
	if (xin <= SPACE + THICK) {
		place = left;
		return 1;
	}
	else if (3 * SPACE - THICK <= xin) {
		place = right;
		return 1;
	}
	return inn;
}