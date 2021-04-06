#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	// Constructor
	ModuleScene();

	// Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate();

public:
	
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* stageTexture = nullptr;
	
	// The sprite rectangle for the ground
	SDL_Rect ground;

	// The sprite section for the background
	SDL_Rect background;

	// The different sprite sections for the flag
	Animation flag;

	// The different sprite sections for the girl
	Animation girl;

	// The sprite section for the ship
	SDL_Rect ship;

	// The timer used to move the ship
	float shipMovementTimer = 0.0f;

	// The position at which we render the ship
	int shipPosition = -5;

	// The movement direction the ship is taking
	int shipMovement = 1;
};

#endif // __MODULESCENE_H__