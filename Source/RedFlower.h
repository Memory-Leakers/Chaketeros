#ifndef _REDFLOWER_H_
#define _REDFLOWER_H_

#include "Obstacle.h"
#include "Application.h"

class RedFlower : public Obstacle
{
public:
	//Constructor
	RedFlower();
	RedFlower(iPoint pos, SDL_Texture* tex, Particle* dieParticle,Tile* tile);

	//Destructor
	~RedFlower();

	// Metodos
	void PostUpdate() override;
	void Die() override;
	void OnCollision(Collider* col) override;

private:
	Particle* dieParticle = nullptr;
	SDL_Rect renderRect;
	Tile* currentTileMap = nullptr;
};

#endif // !_REDFLOWER_H_






