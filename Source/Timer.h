#ifndef _TIMER_H_
#define _TIMER_H_

#include "Globals.h"
#include "External/SDL/include/SDL.h"

class Timer
{
private:

	static Timer* sInstance;
	
	uint mStartTicks;
	uint mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

public:

	static Timer* Instance();
	static void Release();

	void Reset();
	float getDeltaTime();

	void setTimeScale(float t);
	float getTimeScale();

	void Update();

private:

	Timer();
	~Timer();
};

#endif
