#include "DrawKolam.h"

bool DrawKolam::Init() {
	printf("kolam Started");
	return true;
}
void DrawKolam::Update() {}

void DrawKolam::Render() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}