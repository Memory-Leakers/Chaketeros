#ifndef _NUMTEXT_H_
#define _NUMTEXT_H_

#include "External/SDL/include/SDL_rect.h"
#include "Application.h"

class NumText
{
private:

	SDL_Texture* texFonts;

	SDL_Rect fonts[2][10];
	SDL_Rect chars[2];

public:
	NumText();
	~NumText();

	void Start();

	void DrawNum(int num, iPoint pos, float scale = 3.0f, int layer = 2, float orderInLayer = 0.0f, int font = 0);
	void DrawChar(int character, iPoint pos);
};

#endif
