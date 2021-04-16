#ifndef _MODULEOBSTACLE_H_
#define _MODULEOBSTACLE_H_

#include "Module.h"
#include "Obstacle.h"
#include "Collider.h"


#define MAX_OBSTACLES 2

class Obstacle;

class ModuleObstacle : public Module 
{

public:

	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleObstacle();

	//Destructor
	~ModuleObstacle();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	// Called when a particle collider hits another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	void AddObstacle(const Obstacle& obstacle, iPoint position, Type type = Type::NONE);

private:

	//SDL_Texture* texture = nullptr;

	Obstacle* obstacles[MAX_OBSTACLES] = { nullptr };
};


#endif // !_MODULEOBSTACLE_H_

