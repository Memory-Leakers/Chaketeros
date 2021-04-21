#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"

class YellowFlower : public Obstacle 
{
private:

	SDL_Texture * texDie;

	Animation idle, die;
	Animation *currentAnim = nullptr;

	bool isDead = false;

public: 

	YellowFlower();
	YellowFlower(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie);

	void Die() override;

	void PostUpdate() override;
};

#endif // _YELLOWFLOWER_H_