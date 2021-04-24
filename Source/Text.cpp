#include "Text.h"

Text::Text() {

	blackC = { 0,0,0 };
	whiteC = { 255, 255, 255 };
	redC = { 255, 0, 0 };
}

Text::~Text() {
	delete textSurface;
	delete text;
}

void Text::showText(SDL_Renderer* renderer, int x, int y, std::string message, TTF_Font* testFont, SDL_Color color) {

	textSurface = TTF_RenderText_Solid(testFont,  message.c_str(), color);

	text = SDL_CreateTextureFromSurface(renderer, textSurface);

	textRect.x = x;
	textRect.y = y;
	textRect.h = 0;
	textRect.w = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);
	
	// Clean memory
	TTF_CloseFont(testFont);
	testFont = nullptr;
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}


TTF_Font* Text::getFonts(int size) {
	return TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", size);
}
SDL_Color Text::getColors(Uint8 red, Uint8 green, Uint8 blue) {
	return SDL_Color({ red, green, blue });
}

SDL_Color Text::getColors(int index) {
	switch (index) {
	case 0: return blackC; break;
	case 1: return whiteC; break;
	case 2: return redC; break;
	}
}