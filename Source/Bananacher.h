#ifndef BANANACHER_H
#define BANANACHER_H

#include "Timer.h";

#include "ModuleEnemy.h"
class Bananacher : public ModuleEnemy
{
private: 

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	SDL_Rect* rectBanana;

	Particle dieParticle;

	Timer bananaTimer;

	// current direction
	int currentDir = 0;

	int moveDirContrary[4]{ 1,0,3,2 };

	iPoint moveDir[4] = {
	{ 1, 0 },
	{-1, 0 },
	{ 0,-1 },
	{ 0, 1 } };

	// Random Mov variable
	int randomMoveDirIndex = 0;

private:
	int RandomMov();

public:

	Bananacher();
	Bananacher(iPoint spawnPos, SDL_Texture* tex, Tile* tileMap);
	~Bananacher();

	void FixedUpdate();

	bool Start() override;

	UpdateResult PreUpdate() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void OnCollision(Collider* col) override;

	void Die() override;
};

#endif // !BANANACHER_H