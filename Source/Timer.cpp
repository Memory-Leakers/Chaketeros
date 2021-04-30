#include "Timer.h"

Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer()
{
}

void Timer::Reset()
{
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

float Timer::getDeltaTime()
{
	return mDeltaTime;
}

void Timer::setTimeScale(float t)
{
	mTimeScale = t;
}

float Timer::getTimeScale()
{
	return mTimeScale;
}

float Timer::getExecuteTime(bool second)
{
	if (second)
	{
		return  (SDL_GetTicks() - (SDL_GetTicks() % 1000) ) * 0.001f; 
	}

	return SDL_GetTicks();
}

float Timer::Update()
{
	float frame2frame = SDL_GetTicks() - lastTime;
	lastTime = SDL_GetTicks();

	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;

	return (frame2frame * 0.001f);
}


