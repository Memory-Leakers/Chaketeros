#include "Debug.h"
#include "Application.h"
#include "Player.h"
#include "Tile.h"
#include "Obstacle.h"

#include <iostream>
using namespace std;

Debug::Debug(Obstacle** obstacles)
{
	this->obstacles = obstacles;
}

Debug::~Debug()
{

}

void Debug::AddUpFlame()
{
	App->scene->playerSettings->powerUpFlame++;
}

void Debug::PowerUpPosition()
{
	debugPowerUpPosition = !debugPowerUpPosition;
}

void Debug::PlayerGodMod(Player* player)
{
	player->godMode = !player->godMode;
}

void Debug::PlayerPosInConsole(Player* player)
{
	player->posMode = !player->posMode;

	if (player->posMode)
	{
		player->lastTilePos = player->getCurrentTilePos();
		player->tileMap->LevelsTileMaps[App->scene->currentLevel][player->lastTilePos.y - 1][player->lastTilePos.x] = -1;
	}
	else
	{
		player->tileMap->LevelsTileMaps[App->scene->currentLevel][player->tilePos.y - 1][player->tilePos.x] = 0;
	}
}

void Debug::DrawMapInConsole(Tile* tile, int gridX, int gridY)
{
	system("cls");
	cout << endl;

	for (int i = 0, k = 0; i < gridY; ++i)
	{
		for (int j = 0; j < gridX; ++j)
		{
			switch (tile->LevelsTileMaps[App->scene->currentLevel][i][j])
			{
				case -1: cout << "P,"; break;
				case 10: cout << "G,"; break;
				default: cout << tile->LevelsTileMaps[App->scene->currentLevel][i][j] << ","; break;
			}
		}
		cout << endl;
	}
}

void Debug::PrintDebugInformation()
{
	cout << endl;
	cout << "F1: On/Off GodMod" << endl;
	cout << "F2: On/Off Collision box" << endl;
	cout << "F3: Instant lose" << endl;
	cout << "F4: Instant win" << endl;
	cout << "F5: On/Off PowerUp position" << endl;
	cout << "F6: On/Off Mover A* path" << endl;
	cout << "F7: On/Off Camera (move with dirArrown)" << endl;
	cout << "F10: On/Off Draw player pos in console map (use with Q)" << endl;
	cout << "Q: Update console tileMap" << endl;
	cout << "M: bomb flame powerUp" << endl;
}

void Debug::Win(Player* player, iPoint winPos)
{
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr && obstacles[i]->CompareName("CoreMecha"))
		{
			obstacles[i]->Die();
		}
	}
	player->position = winPos;
}

void Debug::GameOver()
{
	App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90);
}

void Debug::Update()
{
}

void Debug::DrawPowerUpPosition()
{
	// Draw powerUpPos
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (debugPowerUpPosition == true && obstacles[i] != nullptr && obstacles[i]->powerUp != 0)
		{
			App->render->AddRectRenderQueue({ obstacles[i]->getPosition().x + 2,obstacles[i]->getPosition().y + 2,12,12 }, { 0,0,255,255 });
		}
	}
}
