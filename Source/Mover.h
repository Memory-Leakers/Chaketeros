#ifndef _MOVER_H_
#define _MOVER_H_

#include "ModuleEnemy.h"
class Mover : public ModuleEnemy
{
private:
	int moveRand = rand() % 4;

protected:

	void die();

	void movement();

public:

	Mover(iPoint position);

	~Mover();

	bool Start();
	UpdateResult Update();
	UpdateResult PostUpdate();

	void onCollision(Collider* otherCol);

	iPoint position;
	Collider* col = nullptr;
	int speed = 1; //Movement only

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
};

#endif // !_MOVER_H_
