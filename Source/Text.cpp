#include "Text.h"

Text::Text() {
	Font80 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 80);
	Font50 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 50);
	Font35 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 35);
	Font20 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 20);
	Font10 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 10);

	blackC = { 0,0,0 };
	whiteC = { 255, 255, 255 };
	redC = { 255, 0, 0 };
}

void Text::showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color) {

	textSurface = TTF_RenderText_Solid(testFont, message, color);

	text = SDL_CreateTextureFromSurface(renderer, textSurface);
	textRect.x = x;
	textRect.y = y;
	textRect.h = 0;
	textRect.w = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
}
