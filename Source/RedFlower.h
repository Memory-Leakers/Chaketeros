#ifndef _REDFLOWER_H_
#define _REDFLOWER_H_

#include "Obstacle.h"
#include "Application.h"

class RedFlower : public Obstacle
{
public:
	//Constructor
	RedFlower();
	RedFlower(iPoint pos, SDL_Texture* tex);

	//Destructor
	~RedFlower();

	// Metodos
	void PostUpdate() override;
	void Die() override;

public:
	// x , y
	iPoint position;
	//Animation variables
	Animation idleAnim;
	Animation DieAnim;
	Animation* CurrentAnimation = nullptr;
};

#endif // !_REDFLOWER_H_






