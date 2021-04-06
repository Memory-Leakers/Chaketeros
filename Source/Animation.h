#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "External/SDL/include/SDL_rect.h"

#define MAX_FRAMES 25

class Animation
{
public:

	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:

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
		current_frame += speed;
		if (current_frame >= last_frame) current_frame = 0;
	}

	SDL_Rect& GetCurrentFrame()
	{
		return frames[(int)current_frame];
	}
};

#endif	// __ANIMATION_H__