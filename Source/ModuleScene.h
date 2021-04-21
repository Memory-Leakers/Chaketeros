#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"

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
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;

public:
	//textura mapa
	SDL_Texture* textmap;
	//Textura UI 
	SDL_Texture* textUI;
};

#endif // __MODULESCENE_H__