#ifndef  _COREMECHA_H
#define _COREMECHA_H

#include "Obstacle.h"

class CoreMecha : public Obstacle
{
private:

	SDL_Texture* texDie = nullptr;

	SDL_Rect renderRect;

	//Animation idle, die;
	Animation* currentAnim = nullptr;

	Particle dieParticle;

	bool isDead = false;

	Tile* currentTileMap;

public:

	CoreMecha();
	CoreMecha(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie, Particle* destroyed, Tile* tile);

	void Die() override;

	void PostUpdate() override;

	void OnCollision(Collider* col) override;
};

#endif // ! _COREMECHA_H