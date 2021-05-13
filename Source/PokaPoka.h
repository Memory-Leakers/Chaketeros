#ifndef _POKAPOKA_H_
#define _POKAPOKA_H_

#include "ModuleEnemy.h"
#include "Timer.h"

class PokaPoka : public ModuleEnemy
{
private:
	int moveRand = rand() % 4;
	int pC = 0;
	iPoint nPoint;
	Particle* dieParticle = nullptr;
	iPoint* playerPos = nullptr;

	Timer attackTimer;
	Timer moveTimer;
	int attacking = 3;

private:

	void attack();
	void movement();

public:
		
	iPoint position;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation attackAnim;

	int speed = 1; //Movement only

public:
	PokaPoka(int x, int y, iPoint* playerPos, Tile* level1Tile);

	~PokaPoka();

	bool Start();

	UpdateResult Update();
	UpdateResult PostUpdate();

	void OnCollision(Collider* col);

	void die() override;


};

#endif // !_POLAPOLA_H_

