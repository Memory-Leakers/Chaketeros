#ifndef _SCENELEVELBOSS_H_
#define _SCENELEVELBOSS_H_

#include "Scene.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "Tile.h"
#include "Obstacle.h"
#include "ModuleCollisions.h"

#define SCENE_OBSTACLES_NUM 256

class SceneLevelBoss : public Scene
{
private:
	SDL_Texture* texBananacher = nullptr;;
	SDL_Texture* texSaru = nullptr;
	SDL_Texture* texMap = nullptr;
	SDL_Texture* texBomb = nullptr;
	SDL_Texture* texUI = nullptr;
	SDL_Texture* texMiscUI = nullptr;

	SDL_Rect recUIbar = { 0,0,256,24 };

	Obstacle* obstacles[SCENE_OBSTACLES_NUM] = { nullptr };

public:
	Tile* tileMap = nullptr;

public:
	SceneLevelBoss();

	// Destructor
	~SceneLevelBoss();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void WillCollision(Collider* c1, Collider* c2) override;

	bool CleanUp(bool finalCleanUp = true) override;

	void CreateScene();

	void InitAssets();
};
#endif

