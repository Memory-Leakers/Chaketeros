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
	float lastTime = 0;

public:

	Timer();
	~Timer();

	void Reset();
	float getDeltaTime();

	void setTimeScale(float t);
	float getTimeScale();

	float getExecuteTime(bool second = false);

	float Update();

};

#endif
