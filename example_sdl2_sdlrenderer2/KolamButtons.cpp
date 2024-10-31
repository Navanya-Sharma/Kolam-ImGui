#include "KolamButtons.h"

KolamButton* butts = NULL;


SDL_Color ButtonStateColors[4] = {
		{ 0xFC, 0x72, 0x52, 0 }, //Outside
		{ 255,255,255,0 }, //Inside
		{ 255,255,255,0 }, //pressed
		{ 255,255,255,0 } //Just Pressed
};

KolamButton::KolamButton() {
	pos.x = 0;
	pos.y = 0;

	place = left;
	st = Outside;
	cur = 2;
	bw = SPACE + THICK;
	bh = 2 * SPACE;
}

KolamButton::~KolamButton() {
	pos = { NULL,NULL };
	place = left;
	cur = NULL;
	bw = NULL;
	bh = NULL;
}

void KolamButton::SetPosition(int x, int y, buttonType w) {
	pos.x = x;
	pos.y = y;
	place = w;

	switch (place)
	{
	case top:
	case bottom:
		bw = 4 * SPACE;
		bh = bh - SPACE;
		break;
	}
	//render();

}

void KolamButton::Render(ImVec4 BGcolor) {
	
	SDL_Color borderColor = ButtonStateColors[st];

	//Clear the screen
	SDL_Rect a = { pos.x, pos.y, bw, bh };
	SDL_SetRenderDrawColor(gRenderer, (Uint8)(BGcolor.x * 255), (Uint8)(BGcolor.y * 255), (Uint8)(BGcolor.z * 255), (Uint8)(BGcolor.w * 255));
	SDL_RenderFillRect(gRenderer, &a);


	if (cur == 2) {
		//Set Border
		SDL_SetRenderDrawColor(gRenderer, borderColor.r, borderColor.g, borderColor.b, 0xFF);
		SDL_RenderDrawRect(gRenderer, &a);
		return;
	}
	//Render the image according to the current sprite
	switch (place) {
	case right: case left:
		sheetLR.Render(pos.x, pos.y, &ImgLR[cur], bw, bh, (place - 1) * 90.0); break;
	case bottom: case top:
		sheetUD.Render(pos.x, pos.y, &ImgUD[cur], bw, bh, place * 90.0);break;
	}

	//Set Border
	SDL_SetRenderDrawColor(gRenderer, borderColor.r, borderColor.g, borderColor.b, 0xFF);
	SDL_RenderDrawRect(gRenderer, &a);
}

void KolamButton::ChangeSprite(int n) {
	if (n == -1)
		cur = (cur + 1) % 3;
	else
		cur = n;
}

void KolamButton::ChangeState(buttonState newst) {
	st = newst;
}

int KolamButton::GetSprite()
{
	return cur;
}

