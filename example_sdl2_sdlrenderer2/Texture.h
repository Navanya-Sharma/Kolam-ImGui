#pragma once
#include<SDL.h>
#include<imgui.h>

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
		void SetBlendMode(SDL_BlendMode a);
		//bool LoadFromRenderedText(std::string textureText, SDL_Color textColor, int textWidth, int bold = 0);

	private:
		SDL_Texture* text;
		int wd;
		int ht;

};

extern Texture dot, sheetUD, sheetLR;

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);
int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);

bool MakeDot(ImVec4 color);
bool MakeSheetLR(ImVec4 color);
bool MakeSheetUD(ImVec4 color);