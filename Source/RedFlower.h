#ifndef _REDFLOWER_H_
#define _REDFLOWER_H_

#include "Obstacle.h"
#include "Application.h"

class RedFlower : public Obstacle
{
private:
	Particle dieParticle;

	SDL_Rect renderRect;

	Tile* currentTileMap = nullptr;

public:
	//Constructor
	RedFlower();

	RedFlower(iPoint pos, SDL_Texture* tex,Tile* tile);

	//Destructor
	~RedFlower();

	// Metodos
	void PostUpdate() override;

	void Die() override;

	void OnCollision(Collider* col) override;
};

#endif // !_REDFLOWER_H_






