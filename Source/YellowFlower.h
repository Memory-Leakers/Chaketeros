#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"

class YellowFlower : public Obstacle 
{
private:

	SDL_Texture* dieTexture;

	Animation idle, die;
	Animation* currentAnim;

public: 

	YellowFlower();

	void PostUpdate() override;

	void Die() override;

};



#endif // _YELLOWFLOWER_H_