#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Texture.h"
#include "core.h"

Texture dot, sheetUD, sheetLR;

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

void Texture::SetBlendMode(SDL_BlendMode a) {
	SDL_SetTextureBlendMode(text, a);
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

bool MakeDot(ImVec4 color) {
	bool pass = true;

	if (!dot.CreateBlankSheet(SPACE / 3, SPACE / 3, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to make dot sprite\n");
		pass = false;
	}
	else {
		dot.SetBlendMode(SDL_BLENDMODE_BLEND);
		dot.SetAsRenderTarget();
		SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), (Uint8)(color.w * 255));


		SDL_RenderFillCircle(gRenderer, SPACE / 6, SPACE / 6, SPACE / 7);
		SDL_SetRenderTarget(gRenderer, NULL);

	}
	return pass;
}

bool MakeSheetUD(ImVec4 color) {
	bool pass = true;
	if (!sheetUD.CreateBlankSheet(SPACE * 4, SPACE * 2, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to load button sprite\n");
		pass = false;
	}
	else {
		sheetUD.SetBlendMode(SDL_BLENDMODE_BLEND);
		sheetUD.SetAsRenderTarget();

		SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
		SDL_RenderClear(gRenderer);
		float y;

		SDL_Rect rec = { 0,0,THICK,1 };
		//Draws the triangle
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), (Uint8)(color.w * 255));

		for (float x = SPACE;x < 2 * SPACE;x += 1) {
			y = -x + 2 * SPACE;
			rec.x = x - THICK / 2; rec.y = y;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		for (float x = 2 * SPACE;x < 3 * SPACE;x += 1) {
			y = x - 2 * SPACE;
			rec.x = x - THICK / 2; rec.y = y;
			SDL_RenderFillRect(gRenderer, &rec);
		}
		//Draws the circle
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), (Uint8)(color.w * 255));

		for (int x = -THICK * 0.3; x < 0.4 * THICK; x++) {
			SDL_RenderDrawCircle(gRenderer, 2 * SPACE, 3 * SPACE, (1.414 * SPACE) + x);
		}

		SDL_SetRenderTarget(gRenderer, NULL);

		ImgUD[0] = { 0,0, SPACE * 4, SPACE };
		ImgUD[1] = { 0, SPACE, SPACE * 4, SPACE };
	}
	return pass;
}

bool MakeSheetLR(ImVec4 color) {
	bool pass = true;
	if (!sheetLR.CreateBlankSheet(2 * (SPACE + THICK), 2 * SPACE, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to load button sprite\n");
		pass = false;
	}
	else {
		sheetLR.SetBlendMode(SDL_BLENDMODE_BLEND);
		sheetLR.SetAsRenderTarget();

		SDL_SetRenderDrawColor(gRenderer, 0,0,0,0);
		SDL_RenderClear(gRenderer);
		float y;
		SDL_Rect rec = { 0,0,1,THICK };

		//Draws lines
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), (Uint8)(color.w * 255));

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
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(color.x * 255), (Uint8)(color.y * 255), (Uint8)(color.z * 255), (Uint8)(color.w * 255));

		for (int x = -0.3 * THICK; x < 0.4 * THICK; x++) {
			SDL_RenderDrawCircle(gRenderer, -SPACE + THICK, SPACE, (1.414 * SPACE) + x);
		}

		SDL_SetRenderTarget(gRenderer, NULL);
		ImgLR[1] = { 0,0, sheetLR.GetWidth() / 2, sheetLR.GetHeight() };
		ImgLR[0] = { sheetLR.GetWidth() / 2,0, sheetLR.GetWidth() / 2, sheetLR.GetHeight() };
	}
	return pass;
}

