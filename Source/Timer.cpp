#include "Timer.h"

Timer* Timer::sInstance[] = { NULL };
int Timer::instanceIndex = 0;

Timer* Timer::Instance()
{
	for (int i = 0; i < 5; i++)
	{
		if (sInstance[i] == nullptr)
		{
			sInstance[i] = new Timer();
			return sInstance[i];
			break;
		}
	}
	
}

void Timer::Release()
{
	for (int i = 0; i < 5; i++)
	{
		delete sInstance[i];
		sInstance[i] = nullptr;
	}
}

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

void Timer::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;
}


