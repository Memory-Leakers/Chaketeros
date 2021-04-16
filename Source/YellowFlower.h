#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"

class YellowFlower : Obstacle 
{
private:

	Animation idle, die;


public: 
	YellowFlower(SDL_Rect r, int flag, bool destructible, Collider* collider, SDL_Texture* texture);

	void Die() override;

};



#endif // _YELLOWFLOWER_H_