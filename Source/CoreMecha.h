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

	bool isDead = false;

public:

	CoreMecha();
	CoreMecha(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie);

	void Die() override;

	void PostUpdate() override;
};

#endif // ! _COREMECHA_H