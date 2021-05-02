#ifndef _STONE_H_
#define _STONE_H_

#include "Obstacle.h"

class Stone : public Obstacle
{
private:
	SDL_Rect renderRect;
public:
	//Constructor

	Stone();
	Stone(iPoint pos, SDL_Texture* tex);

	void PostUpdate() override;
	
};

#endif // _ROCK_H_