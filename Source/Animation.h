#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "External/SDL/include/SDL_rect.h"

#define MAX_FRAMES 12

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	bool hasIdle = true;

private:
	SDL_Rect frames[MAX_FRAMES];
	int loopCount = 0;
	float current_frame = 0.0f;
	int last_frame = 0;

public:

	float getCurrentFrameF()
	{
		return current_frame;
	}

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	void Reset()
	{
		current_frame = 0;
	}

	void Update()
	{
		
		if (hasIdle) {
			current_frame = 0;
		}
		else {
			current_frame += speed;
			if (current_frame >= last_frame && loop) current_frame = 0;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		return frames[(int)current_frame];
	}

	bool HasFinished()
	{
		if(current_frame >= last_frame && !loop)
		{
			return true;
		}

		return false;
	}
};

#endif	// __ANIMATION_H__