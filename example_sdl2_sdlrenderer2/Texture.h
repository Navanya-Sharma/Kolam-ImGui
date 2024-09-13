#pragma once
#include "common.h"

class Texture{
	public:
		Texture();
		~Texture();

		bool LoadTexture(std::string p);
		bool CreateBlankSheet(int width, int height, SDL_TextureAccess access);
		void SetAsRenderTarget();
		void Render(int x, int y, SDL_Rect* clip = NULL, int desW = NULL, int desH = NULL, double angle = 0.0, int pop = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int GetHeight();
		int GetWidth();
		//bool LoadFromRenderedText(std::string textureText, SDL_Color textColor, int textWidth, int bold = 0);

	private:
		SDL_Texture* text;
		int wd;
		int ht;

};

extern Texture dot, sheetUD, sheetLR;

