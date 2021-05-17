#ifndef _YELLOWFLOWER_H_
#define _YELLOWFLOWER_H_

#include "Obstacle.h"
#include "Tile.h"

class YellowFlower : public Obstacle 
{
private:

	SDL_Rect renderRect;

	Particle dieParticle;

	Tile* currentTileMap;

	int hasPowerUp = 0; // Luego se cambia por int ya que habra mas tipos de power ups

public: 
	//Constructor
	YellowFlower();

	YellowFlower(iPoint pos, SDL_Texture* tex, Tile* tile, int hasPowerUp = 0);

	void Die() override;

	void PostUpdate() override;

	void OnCollision(Collider* col) override;

};

#endif // _YELLOWFLOWER_H_