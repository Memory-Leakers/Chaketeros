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

	bool hasPowerUp = false; // Luego se cambia por int ya que habra mas tipos de power ups

public: 
	//Constructor
	YellowFlower();

	YellowFlower(iPoint pos, SDL_Texture* tex, Tile* tile, bool hasPowerUp = false);

	void Die() override;

	void PostUpdate() override;

	void OnCollision(Collider* col) override;

};

#endif // _YELLOWFLOWER_H_