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

	enum FadeSteps {
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};

	int currentFrame, maxFrames;

	FadeSteps currentStep;

	SDL_Rect screenRect;

public:

	bool isFadeInDone, isFadeOutDone;

	static FadeInOut* Instance();

	void Update();

	void FadeIn(int time);

	void FadeOut(int time);

	static void Release();
};

#endif