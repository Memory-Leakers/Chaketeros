#include "FadeInOut.h"

FadeInOut* FadeInOut::sFadeInOut = nullptr;


FadeInOut::FadeInOut()
{
	currentStep = FADE_NONE;
	currentFrame = 0;
	maxFrames = 0;
	screenRect = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

FadeInOut::~FadeInOut()
{
}

FadeInOut* FadeInOut::Instance()
{
	if (sFadeInOut == nullptr)
	{
		sFadeInOut = new FadeInOut();
	}
	return sFadeInOut;
}

void FadeInOut::Update()
{
	if (currentStep == FADE_NONE) return;

	if (currentStep == FADE_IN)
	{
		if (currentFrame != maxFrames)
		{
			currentFrame++;
		}
		else 
		{
			isFadeInDone = true;
			currentStep = FADE_NONE;
		}
		float fadeRatio = (float)currentFrame / (float)maxFrames;

		App->render->AddRectRenderQueue(screenRect, { 0,0,0,(Uint8)(fadeRatio * 255.0f) });
	}

	if (currentStep == FADE_OUT)
	{
		if (currentFrame != 0)
		{
			currentFrame--;
		}
		else
		{
			isFadeOutDone = true;
			currentStep = FADE_NONE;
		}
		float fadeRatio = (float)currentFrame / (float)maxFrames;

		App->render->AddRectRenderQueue(screenRect, { 0,0,0,(Uint8)(fadeRatio * 255.0f) });
	}
}

void FadeInOut::FadeIn(int time)
{
	if (currentStep != FADE_NONE) return;
	currentFrame = 0;
	maxFrames = time;
	currentStep = FADE_IN;

	isFadeOutDone = false;
	isFadeInDone = false;
}

void FadeInOut::FadeOut(int time)
{
	if (currentStep != FADE_NONE) return;
	currentFrame = time;
	maxFrames = time;
	currentStep = FADE_OUT;

	isFadeInDone = false;
	isFadeOutDone = false;
}

void FadeInOut::Release()
{
	if (sFadeInOut != nullptr)
	{
		delete sFadeInOut;
		sFadeInOut = nullptr;
	}
}
