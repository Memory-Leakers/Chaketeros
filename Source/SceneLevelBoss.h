#ifndef _SCENELEVELBOSS_H_
#define _SCENELEVELBOSS_H_

#define MAX_ENEMY 4
#define MAX_POWERUPS 6

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
	SDL_Texture* texMap = nullptr;
	SDL_Texture* texBomb = nullptr;
	SDL_Texture* texUI = nullptr;
	SDL_Texture* texMiscUI = nullptr;
	SDL_Texture* texPowerUps = nullptr;
	SDL_Texture* texPowerUpDestroyed = nullptr;

	SDL_Rect recUIbar = { 0,0,256,24 };

	Obstacle* obstacles[SCENE_OBSTACLES_NUM] = { nullptr };

	ModuleEnemy* enemy[MAX_ENEMY];

	PowerUp* powerUps[MAX_POWERUPS];

	//It is used to prevent the Buff from triggering more than once
	bool saruBuff = false;

	Timer timer;

	//	Number of total seconds
	int totalSeconds = 59;
	//	Number of total minutes
	int minutes = 4;
	// Current second shown on screen
	int currentSecond = 0;
	// Offset for the seconds timer
	int secondsXOffset = 100;

	bool isTimeOut;

	void DebugKeys();

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

	void Spawn(iPoint spawnPos, int objectID) override;

	void CreateScene();

	void InitAssets();
};
#endif
