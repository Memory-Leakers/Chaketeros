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
	ModuleDebug();

	~ModuleDebug();

	void setObstacles(Obstacle** obstacles) { this->obstacles = obstacles; }

	void AddUpFlame();

	void PowerUpPosition();

	void PlayerGodMod(Player* player);

	void PlayerPosInConsole(Player* player);

	void DrawMapInConsole(Tile* tile, int gridX, int gridY);

	void PrintDebugInformation();

	void Win(Player* player, iPoint winPos);

	void GameOver();

	void DrawPowerUpPosition();
};

#endif // !__MODULE_DEBUG_Hs

