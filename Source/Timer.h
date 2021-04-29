#ifndef _TIMER_H_
#define _TIMER_H_

#include "Globals.h"
#include "External/SDL/include/SDL.h"

class Timer
{
private:

	uint mStartTicks;
	uint mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

public:

	Timer();
	~Timer();

	void Reset();
	float getDeltaTime();

	void setTimeScale(float t);
	float getTimeScale();

	void Update();

	
};

#endif
