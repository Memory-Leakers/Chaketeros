#ifndef _MOVER_H_
#define _MOVER_H_

#include "Timer.h"

#include "ModuleEnemy.h"
#include <vector>
using namespace std;

struct PathNode
{
	iPoint pos; // grid position

	int lastIndex; // last path index
	int dir; // Direction when coming
	int h_cost; // Current price
	int g_cost; // Estimated price
	int total_cost; //  Current price + Estimated price
};

class Mover : public ModuleEnemy
{
private:

	Particle* dieParticle = nullptr;

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	Timer moverTimer;

	iPoint* playerPos = nullptr; // get player position for A star

	iPoint moveDir[4] = {
	 { 1, 0 },
	 {-1, 0 },
	 { 0,-1 },
	 { 0, 1 } };

	bool hasPathToPlayer = false;

	int currentDir = 0; // Current direccion that we will move

	int speed = 1; //Movement onlys

	// A* variable
	int moveDirContrary[4]{ 1,0,3,2 }; // push back direccion A star
	int AStarMoveDirIndex = 0; // get A star result

	// Random Mov variable
	int randomMoveDirIndex = 0; // get RandomMos result

	bool debugAStarPath = false;

private:
	// private metod
	

	// When no detect player
	int RandomMov();

	// Automatic wayfinding
	int AStar();

public:

	// Constructor
	Mover(iPoint spawnPos, iPoint* playerPos, Tile* levelMap);

	// Destructor
	~Mover();

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

#endif // !_MOVER_H_
