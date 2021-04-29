#ifndef _MOVER_H_
#define _MOVER_H_

#include "Timer.h"

#include "ModuleEnemy.h"
#include <vector>
using namespace std;

struct PathNode
{
	int lastIndex;
	iPoint pos;

	int dir;

	int h_cost;
	int g_cost;
	int total_cost;
};

class Mover : public ModuleEnemy
{
private:
	// private variable

	Particle* dieParticle = nullptr;

	iPoint* playerPos = nullptr;

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	bool hasPathToPlayer = false;

	int randomDir;

	vector <int> movePath;

	Timer* moverTimer;

	iPoint moveDir[4]{ 
	 { 1, 0 },
	 {-1, 0 },
	 { 0,-1 },
	 { 0, 1 } };

	int moveDirIndex = 0;

	// private metod
	void die() override;

	void RandomMov();

	int AStar();

	friend class Tile;

public:

	Mover(iPoint spawnPos, iPoint* playerPos, Tile* levelMap);

	~Mover();

	bool Start() override;

	UpdateResult PreUpdate() override;

	UpdateResult Update() override;

	void FixedUpdate();

	UpdateResult PostUpdate() override;

	void OnCollision(Collider* col) override;

	iPoint position;
	
	int speed = 1; //Movement only
};

#endif // !_MOVER_H_
