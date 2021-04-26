#ifndef _COIN_H_
#define _COIN_H_

#include "Obstacle.h"

class Coin : public Obstacle
{
private:
	Animation idle;
	Animation* currentAnim = nullptr;
public:

	~Coin();

	Coin(iPoint position, SDL_Texture* texture);

	void Update() override;

	void PostUpdate() override;
};


#endif //_COIN_H_!
