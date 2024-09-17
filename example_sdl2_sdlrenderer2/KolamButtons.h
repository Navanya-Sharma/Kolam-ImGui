#pragma once
#include <SDL.h>
#include "core.h"
#include "Texture.h"


enum buttonType {
	top,
	right,
	bottom,
	left,
};

extern SDL_Color ButtonStateColors[4], ButtonStateBorder[4];

class KolamButton {
	public:
		enum buttonState {
			Outside,
			Inside,
			Pressed,
			JustPressed,
		};
		KolamButton();
		~KolamButton();
		void SetPosition(int x, int y, buttonType w);
		void Render();
		void ChangeState(buttonState newst);
		void ChangeSprite(int n=-1);
	private:

		SDL_Point pos;
		buttonType place;
		buttonState st;
		int cur;
		int bw;
		int bh;
};

extern KolamButton* butts;

