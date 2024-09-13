#pragma once
#include "common.h"


/*extern enum buttonType {
	top,
	right,
	bottom,
	left,
};*/

extern enum buttonState {
			Outside,
			Inside,
			Pressed,
			JustPressed,
		};

extern SDL_Color ButtonStateColors[4], ButtonStateBorder[4];

class KolamButton {
	public:
		
		KolamButton();
		~KolamButton();
		void setPosition(int x, int y, DrawKolam::buttonType w);
		void render();
		void changeState(buttonState newst);
		void changeSprite();
	private:

		SDL_Point pos;
		DrawKolam::buttonType place;
		buttonState st;
		int cur;
		int bw;
		int bh;
};

extern KolamButton* butts;

