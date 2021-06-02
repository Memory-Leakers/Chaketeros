#ifndef DEBUG_H
#define DEBUG_H

#include "Point.h"

class Player;
class Tile;
class Obstacle;

class Debug
{
private:
	Obstacle** obstacles = nullptr;

	bool debugPowerUpPosition = false;

public:
	Debug(Obstacle** obstacles);

	~Debug();

	void AddUpFlame();

	void PowerUpPosition();

	void PlayerGodMod(Player* player);

	void PlayerPosInConsole(Player* player);

	void DrawMapInConsole(Tile* tile, int gridX, int gridY);

	void PrintDebugInformation();

	void Win(Player* player, iPoint winPos);

	void GameOver();

	void Update();

	void DrawPowerUpPosition();
};

#endif // !DEBUG?H

