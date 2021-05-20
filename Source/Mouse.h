#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "ModuleEnemy.h"
#include "Timer.h"
#include "Tile.h"
#include <vector>
using namespace std;

class Mouse : public ModuleEnemy
{
private:


	Particle dieParticle;

	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	Timer mouseTimer;

	iPoint moveDir[4] = {
	 { 1, 0 },
	 {-1, 0 },
	 { 0,-1 },
	 { 0, 1 } };

	int currentDir = 0; // Current direccion that we will move

	int speed = 2; //Movement onlys

	// Random Mov variable
	int randomMoveDirIndex = 0; // get RandomMos result
	int moveDirContrary[4]{ 1,0,3,2 }; // push back direccion A star
private:

	int RandomMov();

public:

	// Constructor
	Mouse(iPoint spawnPos, SDL_Texture* tex, Tile* levelMap);

	// Destructor
	~Mouse();

	// Update for x second 
	// call in Update
	void FixedUpdate();

	bool Start() override;

	void OnCollision(Collider* col) override;

	UpdateResult PreUpdate() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void Die() override;

};
#endif // !_SNAIL_H_

