#include "Texture.h"

Texture::Texture() {
	text = NULL;
	wd = 0;
	ht = 0;
}

Texture::~Texture() {
	if (text != NULL) {
		SDL_DestroyTexture(text);
		text = NULL;
		wd = 0;
		ht = 0;
	}
}

bool Texture::LoadTexture(std::string p) {
	SDL_Surface* temp = NULL;
	SDL_Texture* temptext = NULL;
	temp = IMG_Load(p.c_str());
	if (temp == NULL) {
		printf("Failed to laod %s! SDL Error:%s\n", p.c_str(), IMG_GetError());
	}
	else {

		SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 0, 0XFF, 0XFF));

		temptext = SDL_CreateTextureFromSurface(gRenderer, temp);
		if (temptext == NULL) {
			printf("Cant convert surface to texture! SDL Error: %s", SDL_GetError());
		}
		else {
			wd = temp->w;
			ht = temp->h;
		}
		SDL_FreeSurface(temp);
	}
	text = temptext;
	return text != NULL;
}

bool Texture::CreateBlankSheet(int width, int height, SDL_TextureAccess access)
{
	text = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
	if (text == NULL)
	{
		printf("Unable to create streamable sheetLR texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		wd = width;
		ht = height;
	}

	return text != NULL;
}

void Texture::SetAsRenderTarget()
{
	SDL_SetRenderTarget(gRenderer, text);
}

void Texture::Render(int x, int y, SDL_Rect* clip, int desW, int desH, double angle, int pop, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect des = { x,y,desW,desH };
	if (desW == NULL) {
		des.w = wd;
	}
	if (desH == NULL) {
		des.h = ht;
	}
	if (SDL_RenderCopyEx(gRenderer, text, clip, &des, angle, center, flip) != 0) {
		printf("Could not Render Texture Eror: %s\n", SDL_GetError());
	}
}

int Texture::GetHeight() {
	return ht;
}

int Texture::GetWidth() {
	return wd;
}

/*bool Texture::LoadFromRenderedText(std::string textureText, SDL_Color textColor, int textWidth, int bold) {

	//Render text surface
	//SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	SDL_Surface* textSurface = NULL;

	if (bold == 1) {
		textSurface = TTF_RenderText_Solid_Wrapped(BoldFont, textureText.c_str(), textColor, textWidth);
	}
	else {
		textSurface = TTF_RenderText_Solid_Wrapped(gFont, textureText.c_str(), textColor, textWidth);
	}

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		text = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (text == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			wd = textSurface->w;
			ht = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return text != NULL;
}*/

Texture dot, sheetUD, sheetLR;

