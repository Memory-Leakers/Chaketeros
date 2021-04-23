#ifndef _REDFLOWER_H_
#define _REDFLOWER_H_

#include "Obstacle.h"
#include "Application.h"

class RedFlower : public Obstacle
{
public:
	//Constructor
	RedFlower();
	RedFlower(iPoint pos, SDL_Texture* tex, Particle* dieParticle);

	//Destructor
	~RedFlower();

	// Metodos
	void PostUpdate() override;
	void Die() override;

private:
	Particle* dieParticle = nullptr;
	SDL_Rect renderRect;
};

#endif // !_REDFLOWER_H_






