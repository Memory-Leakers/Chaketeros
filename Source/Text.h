#pragma once

#include <string>
#include "External/SDL_ttf/include/SDL_ttf.h"

enum class textColour {
	BLACK = 0,
	WHITE,
	RED
};


class Text {
	private:
		SDL_Surface* textSurface;
		SDL_Texture* text;
		SDL_Rect textRect;

		SDL_Color blackC;
		SDL_Color whiteC;
		SDL_Color redC;

		TTF_Font* font30 = TTF_OpenFont("Assets/Fonts/advanced_pixel.ttf", 30);

	protected:

	public:

		Text();

		~Text();

		TTF_Font* getFonts(int size);
		SDL_Color getColors(Uint8 red, Uint8 green, Uint8 blue);
		SDL_Color getColors(int index);

		void showText(SDL_Renderer* renderer, int x, int y, std::string message, int fontSize, SDL_Color color);
};
