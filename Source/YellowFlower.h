#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"

class YellowFlower : public Obstacle 
{
private:

	SDL_Rect renderRect;

	Particle* dieParticle = nullptr;

public: 

	YellowFlower();
	YellowFlower(iPoint pos, SDL_Texture* tex, Particle* dieParticle);

	void Die() override;

	void PostUpdate() override;

	void OnCollision(Collider* col) override;
};

#endif // _YELLOWFLOWER_H_