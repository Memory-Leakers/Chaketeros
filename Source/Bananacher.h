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

	iPoint moveDir[4] = {
	{ 1, 0 },
	{-1, 0 },
	{ 0,-1 },
	{ 0, 1 } };

	// current direction
	int currentDir = 0;
	// Random Mov variable
	int randomMoveDirIndex = 0;

	int moveDirContrary[4]{ 1,0,3,2 };

	int protectCount = 0;

	bool injureAnim = false;

	bool buffed = false;
	Timer buffTimer;

	float rev = 0.05f;

private:

	int RandomMov();

	void ProtectCountdown();

public:

	Bananacher();

	Bananacher(iPoint spawnPos, Tile* tileMap);

	~Bananacher();

	bool Start() override;

	UpdateResult PreUpdate() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void OnCollision(Collider* col) override;

	void FixedUpdate();

	void Die() override;

	Collider* bigCol = nullptr;
};

#endif // !BANANACHER_H
