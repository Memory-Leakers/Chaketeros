#ifndef __MODULE_DEBUG_H
#define __MODULE_DEBUG_H

#include "Module.h"
#include "Point.h"

#include "External/SDL/include/SDL_render.h"

class Player;

class Tile;

class Obstacle;

class ModuleDebug :  public Module
{
private:
	Obstacle** obstacles = nullptr;

	bool debugPowerUpPosition = false;

	bool createObject = false;

	SDL_Texture* texPause = nullptr;

	SDL_Texture* texArrow = nullptr;

	SDL_Texture* texPowerUp = nullptr;

	SDL_Rect recPowers[4] = { { 2,2,16,16 }, { 20,20,16,16 }, { 20,2,16,16 }, { 2,20,16,16 } };
	SDL_Rect returnButton = { 171, 36, 21, 9 }, enterButton = {175,47,14,16};

	iPoint arrowPos[7] = { {64,95},{97,95},{129,95},{65,139},{97,139},{128,139},{166,139} };

	// For camera debug
	iPoint cameraTempPos;

	int arrowPosPointer = 0;

	uint createErrorSFX;
	uint selectOptionSFX;

	Tile* currentTile = nullptr;

	iPoint spawnPoint = { 0, 0 };

	Player* player;

public:
	float pauseTimeOffset = 0;

	bool debugCamera = false;

	bool debugColBox = false;

public:
	ModuleDebug();

	~ModuleDebug();

	bool Start() override;

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void InitDebug(Obstacle** obstacles, Tile* tile, Player* player);

	void ConstructMode();

	void CalPauseTimeOffset();

	void AddUpFlame();

	void PowerUpPosition();

	void PlayerGodMod();

	void PlayerPosInConsole();

	void DrawMapInConsole(Tile* tile, int gridX, int gridY);

	void PrintDebugInformation();

	void Win(iPoint winPos, int cameraX = 0);

	void PauseOnOff();

	void GameOver();

	void DrawPowerUpPosition();
};

#endif // !__MODULE_DEBUG_Hs

