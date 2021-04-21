#ifndef _REDFLOWER_H_
#define _REDFLOWER_H_

#include "Obstacle.h"


class RedFlower : public Obstacle
{
public:
	//Constructor
	RedFlower();
	//Destructor
	~RedFlower();

	void PostUpdate()override;
	void DieUpdate();
public:
	// x , y
	iPoint position;
	//Animation variables
	Animation idleAnim;
	Animation DieAnim;
	Animation* CurrentAnimation = nullptr;
	//Texture
	
};

#endif // !_REDFLOWER_H_
