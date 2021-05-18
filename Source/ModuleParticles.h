#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Particle.h"
#include "Collider.h"
#include "Timer.h"

#include "Application.h"

#include "External/SDL/include/SDL_timer.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collision;

class ModuleParticles : public Module
{
public:
	// Constructor
	// Initializes all the particles in the array to nullptr
	ModuleParticles();

	//Destructor
	~ModuleParticles();

	// Called when the module is activated
	// Loads the necessary textures for the particles
	bool Start() override;

	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	// Iterates all the particles and calls its Update()
	// Removes any "dead" particles
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Iterates all the particles and draws them
	UpdateResult PostUpdate() override;

	// Called on application exit
	// Destroys all active particles left in the array
	bool CleanUp() override;

	void CleanUpScene();	//Our CleanUp to destroy a scene

	// Called when a particle  hits another 
	void OnCollision(Collider* c1, Collider* c2) override;

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, int x, int y, Type Type = Type::NONE, float layerOffset = 0.0f, uint delay = 0);

	// Creates a new particle and adds it to the array
	// Param particle	- A template particle from which the new particle will be created
	// Param pos		- Position x,y in the screen (upper left axis)
	// Param delay		- Delay time from the moment the function is called until the particle is displayed in screen
	void AddParticle(const Particle& particle, iPoint pos, Type Type = Type::NONE, bool flipHor = true, float rotation = 0, float layerOffset = 0.0f, uint delay = 0);

private:

	// An array to store and handle all the particles
	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };
public:

	Particle powerUpDestroyed;
};

#endif // __MODULEPARTICLES_H__