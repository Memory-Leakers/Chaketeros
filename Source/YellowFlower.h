#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"

class YellowFlower : public Obstacle 
{
private:

	SDL_Texture* texDie = nullptr;

	SDL_Rect renderRect;

	Particle* dieParticle;

public: 

	YellowFlower();
	YellowFlower(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie, Particle* dieParticle);

	void Die() override;

	void PostUpdate() override;

	void OnCollision(Collider* col) override;
};

#endif // _YELLOWFLOWER_H_