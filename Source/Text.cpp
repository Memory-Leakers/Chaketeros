#include "Text.h"
#include "Application.h"

Text::Text() {

	Font50 = TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", 50);
	Font40 = TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", 40);
	Font35 = TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", 35);
	Font20 = TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", 20);
	Font10 = TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", 10);

	blackC = { 0,0,0 };
	whiteC = { 255, 255, 255 };
	redC = { 255, 0, 0 };

}

Text::~Text() {
	
	TTF_CloseFont(Font50);
	TTF_CloseFont(Font40);
	TTF_CloseFont(Font35);
	TTF_CloseFont(Font20);
	TTF_CloseFont(Font10);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(text);
}

void Text::showText(SDL_Renderer* renderer, int x, int y, std::string message, TTF_Font* font, SDL_Color color) 
{
	//SDL_Surface* surf = TTF_RenderText_Solid(font, message.c_str(), color);;

	if (textSurface == nullptr)
	{
		textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	}

	if (text == nullptr) 
	{
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
	SDL_DestroyTexture(text);
	text = nullptr;
}


TTF_Font* Text::getFonts(int size) {
	/*
	if (tempFont != NULL) 
	{
		TTF_CloseFont(tempFont);
	}

	return TTF_OpenFont("Assets/Fonts/ARCADECLASSIC.ttf", size);
	*/

	switch (size)
	{
	case 50: return Font50; break;
	case 40: return Font40; break;
	case 35: return Font35; break;
	case 20: return Font20; break;
	case 10: return Font10; break;
	}

	return Font50;
}
SDL_Color Text::getColors(Uint8 red, Uint8 green, Uint8 blue) {
	return SDL_Color({ red, green, blue });
}

SDL_Color Text::getColors(int index) 
{
	switch (index)
	{
	case 0: return blackC; break;
	case 1: return whiteC; break;
	case 2: return redC; break;
	}
}
