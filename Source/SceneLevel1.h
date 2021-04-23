#ifndef _SCENELEVEL1_H_
#define _SCENELEVEL1_H_


#include "Scene.h"

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"

struct SDL_Texture;

#define SCENE_OBSTACLES_NUM 128
#define MAX_EMPTY_SPACES 104

class SceneLevel1 : public Scene
{
public:

	SceneLevel1();

	// Destructor
	~SceneLevel1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp(bool finalCleanUp = true) override;

	void CreateYellowFlowers();

	void LoadAsset();

};

#endif