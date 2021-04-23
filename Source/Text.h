#pragma once

#include "External/SDL_ttf/include/SDL_ttf.h"

class Text {
	private:
		SDL_Surface* textSurface;
		SDL_Texture* text;
		SDL_Rect textRect;
		

		TTF_Font* Font80;
		TTF_Font* Font50;
		TTF_Font* Font35;
		TTF_Font* Font20;
		TTF_Font* Font10;
		SDL_Color blackC;
		SDL_Color whiteC;
		SDL_Color redC;
	protected:

	public:

		Text();

		~Text();

		TTF_Font* getFonts(int size) {
			switch (size) {
			case 80: return Font80; break;
			case 50: return Font50; break;
			case 35: return Font35; break;
			case 20: return Font20; break;
			case 10: return Font10; break;
			default: return Font50;
			}
		}
		SDL_Color getColors(int index) {
			switch (index) {
			case 0: return blackC; break;
			case 1: return whiteC; break;
			case 2: return redC; break;
			}
		}

		void showText(SDL_Renderer* renderer, int x, int y, const char* message, TTF_Font* testFont, SDL_Color color);
};
