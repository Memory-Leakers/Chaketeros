#ifndef _SNAIL_H_
#define _SNAIL_H_

#include "ModuleEnemy.h"
#include "Timer.h"
#include "Tile.h"
#include <vector>
using namespace std;

class Snail : public ModuleEnemy
{
private:
	

	Particle dieParticle;

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	Timer snailTimer;

	iPoint moveDir[4] = {
	 { 1, 0 },
	 {-1, 0 },
	 { 0,-1 },
	 { 0, 1 } };

	int currentDir = 0; // Current direccion that we will move

	int speed = 1; //Movement onlys

	// Random Mov variable
	int randomMoveDirIndex = 0; // get RandomMos result
	int moveDirContrary[4]{ 1,0,3,2 }; // push back direccion A star
private:
	
	int RandomMov();

public:

	// Constructor
	Snail(iPoint spawnPos, SDL_Texture* tex, Tile* levelMap);

	// Destructor
	~Snail();

	// Update for x second 
	// call in Update
	void FixedUpdate();

	bool Start() override;

	void OnCollision(Collider* col) override;

	UpdateResult PreUpdate() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void die() override;


};
#endif // !_SNAIL_H_

