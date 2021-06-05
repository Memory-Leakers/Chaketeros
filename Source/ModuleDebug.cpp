#include "ModuleDebug.h"

#include "ModuleInput.h"
#include "Application.h"
#include "Player.h"
#include "Tile.h"
#include "Obstacle.h"

#include <iostream>
using namespace std;

ModuleDebug::ModuleDebug()
{
	pauseIgnore = true;
}

ModuleDebug::~ModuleDebug()
{
}

UpdateResult ModuleDebug::Update()
{
	// Toggle Fullscreen
	if (App->input->keys[SDL_SCANCODE_F] == KEY_DOWN)
	{
		App->FullScreenDesktop = !App->FullScreenDesktop;

		if (App->FullScreenDesktop)
		{
			SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			App->ScreenSize = 1;
		}
		else
		{
			SDL_SetWindowFullscreen(App->window->window, 0);
			App->ScreenSize = 3;
		}

	}

	GamePad& pad = App->input->pads[0];
	//Pause logic
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || pad.start == KEY_DOWN) 
	{
		App->isPaused = !App->isPaused;
		CalPauseTimeOffset();
	}

#pragma region Camera movement

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN)
	{
		debugCamera = !debugCamera;
		if (!debugCamera)
		{
			App->render->camera.y = 0;
			App->render->camera.x = 0;
		}
	}

	if (debugCamera)
	{
		// Handle positive vertical movement
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT) App->render->camera.y -= App->render->cameraSpeed;

		// Handle negative vertical movement
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) App->render->camera.y += App->render->cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) App->render->camera.x += App->render->cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) App->render->camera.x -= App->render->cameraSpeed;
	}

#pragma endregion

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleDebug::PostUpdate()
{
	if(App->isPaused)
	{
		ConstructMode();
	}
	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleDebug::InitDebug(Obstacle** obstacles)
{
	this->obstacles = obstacles;

	pauseTimeOffset = 0;
}

void ModuleDebug::ConstructMode()
{
	App->render->AddRectRenderQueue({ 0,0, SCREEN_WIDTH ,SCREEN_HEIGHT }, { 0,0,255,50});
}

void ModuleDebug::CalPauseTimeOffset()
{
	if (App->isPaused)
	{
		pauseTimeOffset = (SDL_GetTicks() * 0.001f) - pauseTimeOffset;
	}
	else
	{
		pauseTimeOffset = (SDL_GetTicks() * 0.001f) - pauseTimeOffset;
	}
}

void ModuleDebug::AddUpFlame()
{
	App->scene->playerSettings->powerUpFlame++;
}

void ModuleDebug::PowerUpPosition()
{
	debugPowerUpPosition = !debugPowerUpPosition;
}

void ModuleDebug::PlayerGodMod(Player* player)
{
	player->godMode = !player->godMode;
}

void ModuleDebug::PlayerPosInConsole(Player* player)
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

void ModuleDebug::DrawMapInConsole(Tile* tile, int gridX, int gridY)
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

void ModuleDebug::PrintDebugInformation()
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
	cout << "Z: bomb flame powerUp" << endl;
}

void ModuleDebug::Win(Player* player, iPoint winPos, int cameraX)
{
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr && obstacles[i]->CompareName("CoreMecha"))
		{
			obstacles[i]->Die();
		}
	}
	player->position = winPos;
	App->render->CameraMove({ cameraX,0 });
}

void ModuleDebug::GameOver()
{
	App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90);
}

void ModuleDebug::DrawPowerUpPosition()
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
