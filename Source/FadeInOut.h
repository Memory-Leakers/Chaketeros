#ifndef _FADEINOUT_H_
#define _FADEINOUT_H_

#include "Application.h"

#include "External/SDL/include/SDL_rect.h"

class FadeInOut
{
private:

	static FadeInOut* sFadeInOut;

	FadeInOut();
	~FadeInOut();

	int currentFrame, maxFrames;

	SDL_Rect screenRect;

public:

	enum FadeSteps {
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};

	FadeSteps currentStep;

	bool isFadeInDone, isFadeOutDone;

	static FadeInOut* Instance();

	void Update();

	void FadeIn(int time);

	void FadeOut(int time);

	static void Release();
};

#endif