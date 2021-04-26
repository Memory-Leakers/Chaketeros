#include "Text.h"
#include "Application.h"

Text::Text() {

	if (!TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 80)) {
		std::cout << TTF_GetError();
	}

	//Font80 =
	Font50 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 50);
	Font35 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 35);
	Font20 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 20);
	Font10 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 10);

	blackC = { 0,0,0 };
	whiteC = { 255, 255, 255 };
	redC = { 255, 0, 0 };
}

Text::~Text() {

	TTF_CloseFont(Font80);
	TTF_CloseFont(Font50);
	TTF_CloseFont(Font35);
	TTF_CloseFont(Font20);
	TTF_CloseFont(Font10);

	delete textSurface;
	delete text;
}

void Text::showText(SDL_Renderer* renderer, int x, int y, std::string message, TTF_Font* font, SDL_Color color) {

	if (textSurface == NULL) {
		textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	}

	if (text == NULL) {
		text = SDL_CreateTextureFromSurface(renderer, textSurface);
	}

	textRect.x = x;
	textRect.y = y;
	textRect.h = 0;
	textRect.w = 0;

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

	SDL_RenderCopy(renderer, text, NULL, &textRect);

	// Clean memory
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
}


TTF_Font* Text::getFonts(int size) {
	/*
	if (tempFont != NULL) {
		TTF_CloseFont(tempFont);
	}

	return TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", size);
	*/

	switch (size) {
	case 80: return Font80; break;
	case 50: return Font50; break;
	case 35: return Font35; break;
	case 20: return Font20; break;
	case 10: return Font10; break;
	default: return Font50;
	}

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
