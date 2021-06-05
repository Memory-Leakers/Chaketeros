#ifndef __MODULE_DEBUG_H
#define __MODULE_DEBUG_H

#include "Module.h"
#include "Point.h"

class Player;

class Tile;

class Obstacle;

class ModuleDebug :  public Module
{
private:
	Obstacle** obstacles = nullptr;

	bool debugPowerUpPosition = false;

public:
	float pauseTimeOffset = 0;

	bool debugCamera = false;

public:
	ModuleDebug();

	~ModuleDebug();

	UpdateResult Update() override;

	UpdateResult PostUpdate() override;

	void InitDebug(Obstacle** obstacles);

	void ConstructMode();

	void CalPauseTimeOffset();

	void AddUpFlame();

	void PowerUpPosition();

	void PlayerGodMod(Player* player);

	void PlayerPosInConsole(Player* player);

	void DrawMapInConsole(Tile* tile, int gridX, int gridY);

	void PrintDebugInformation();

	void Win(Player* player, iPoint winPos, int cameraX = 0);

	void GameOver();

	void DrawPowerUpPosition();
};

#endif // !__MODULE_DEBUG_Hs

