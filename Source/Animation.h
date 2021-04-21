#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "External/SDL/include/SDL_rect.h"

#define MAX_FRAMES 12

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	bool hasIdle = true;

private:
	int loopCount = 0;
	float current_frame = 0.0f;
	int last_frame = 0;

public:

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
		if(hasIdle==false)
		{
		
		}
		if (hasIdle) {
			current_frame = 0;
		}
		else {
			current_frame += speed;
			if (current_frame >= last_frame) current_frame = 0;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		return frames[(int)current_frame];
	}

	bool HasFinished()
	{
		return !loop && loopCount > 0;
	}
};

#endif	// __ANIMATION_H__