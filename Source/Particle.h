#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Animation.h"
#include "Point.h"
#include "Collider.h"
//#include "External/SDL_image/include/SDL_image.h"

struct SDL_Texture;

class Particle
{
public:
	// Constructor
	Particle();

	// Copy constructor
	Particle(const Particle& p);

	Particle(bool explosion, float lifetime, float animSpeed, SDL_Texture* tex);

	// Destructor
	~Particle();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();

public:
	// Defines the position in the screen
	iPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	iPoint speed;

	// A set of rectangle sprites
	Animation anim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the time when the particle will be spawned
	int frameCount = 0;

	// Defines the total amount of time during which the particle will be active (in miliseconds)
	Uint32 lifetime = 0;

	// The particle's 
	Collider* col  = nullptr;

	SDL_Texture* renderTex = nullptr;
};

#endif //__PARTICLE_H__