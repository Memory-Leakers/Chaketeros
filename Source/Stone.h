#ifndef _STONE_H_
#define _STONE_H_

#include "Obstacle.h"

class Stone : public Obstacle
{
private:

	Animation idle;

public:


	Stone();

	void PostUpdate() override;
	




};




#endif // _ROCK_H_