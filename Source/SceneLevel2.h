#ifndef _SCENELEVEL2_H_
#define _SCENELEVEL2_H_

#include "Scene.h"
#include "Point.h"
#include "Tile.h"

#define LEVEL2_POWERUPS_NUM 5
#define LEVEL2_OBSTACLES 256

class Player;

class Obstacle;

class Tile;

struct SDL_Texture;



class SceneLevel2 : public Scene
{
private:

	Tile* level2TileMap;

	SDL_Rect recUIbar = { 0,0,256,24 };

	SDL_Texture* texMap;
	SDL_Texture* texFG = nullptr;
	SDL_Texture* texUI = nullptr;
	SDL_Texture* texBomb = nullptr;
	SDL_Texture* texStone = nullptr;
	SDL_Texture* texGlassCapsule = nullptr;
	SDL_Texture* texYellowFlower = nullptr;
	SDL_Texture* texEnemies = nullptr;
	SDL_Texture* texItemDestroyed = nullptr;
	SDL_Texture* texCoin = nullptr;
	SDL_Texture* texPowerUpDestroyed = nullptr;
	SDL_Texture* texCoreMecha = nullptr;
	SDL_Texture* texPowerUps = nullptr;
	SDL_Texture* texMiscUI = nullptr;

	uint whistlingSFX, oneMinuteSFX, levelCompleteSFX, extraCoinsBckgSFX;

	int redFlowerIndex, glassCapsuleIndex;

	int coreMechaNum = 3;

	int yellowFlowersNum;

	iPoint powerUpPos[LEVEL2_POWERUPS_NUM];

	iPoint colisionBoxPos;

	Obstacle* sceneObstacles[LEVEL2_OBSTACLES] = { nullptr };

	Player* bomberman;



public:

	SceneLevel2();

	// Destructor
	~SceneLevel2();

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

	void CreateYellowFlowers();

	void CreateCoins();

	void InitAssets();
};

#endif