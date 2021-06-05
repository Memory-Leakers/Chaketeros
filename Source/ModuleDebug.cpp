#include "ModuleDebug.h"

#include "ModuleInput.h"
#include "Application.h"
#include "Player.h"
#include "Tile.h"
#include "Obstacle.h"

#include <iostream>
using namespace std;

iPoint debugPoint = {0, 0};

ModuleDebug::ModuleDebug()
{
	pauseIgnore = true;
}

ModuleDebug::~ModuleDebug()
{
}

bool ModuleDebug::Start()
{
	texArrow = App->textures->Load("Assets/Images/Sprites/My_Sprites/Arrow.png");
	texPause = App->textures->Load("Assets/Images/Sprites/My_Sprites/Pause.png");
	texPowerUp = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/Powerups.png");

	return true;
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
		// Just can be pause in gameScene
		int sceneID = App->scene->currentScene->getID();
		if (sceneID == 4 || sceneID == 5 || sceneID == 6)
		{
			App->isPaused = !App->isPaused;
			createObject = false;
			CalPauseTimeOffset();
		}		
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

	#pragma region ContructMode

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
	{
		debugPoint.x-=16;
		if (debugPoint.x < currentTile->limitMin[App->scene->currentLevel].x)
		{
			debugPoint.x = currentTile->limitMin[App->scene->currentLevel].x;
		}
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
	{
		debugPoint.x+= 16;
		if (debugPoint.x > currentTile->limitMax[App->scene->currentLevel].x)
		{
			debugPoint.x = currentTile->limitMax[App->scene->currentLevel].x;
		}
	}
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
	{
		debugPoint.y-= 16;
		if (debugPoint.y < currentTile->limitMin[App->scene->currentLevel].y)
		{
			debugPoint.y = currentTile->limitMin[App->scene->currentLevel].y;
		}
	}
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
	{
		debugPoint.y+= 16;
		if (debugPoint.y > currentTile->limitMax[App->scene->currentLevel].y)
		{
			debugPoint.y = currentTile->limitMax[App->scene->currentLevel].y;
		}
	}

	#pragma endregion

	if (App->isPaused)
	{
		ConstructMode();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleDebug::PostUpdate()
{
	if(App->isPaused)
	{
		if(!createObject)
		{
			App->render->AddTextureRenderQueue(texPause, { 0 ,0 }, nullptr, 2, 100);

			App->render->AddTextureRenderQueue(texArrow, arrowPos[arrowPosPointer], nullptr, 2, 101);
		}
		else
		{
			SDL_Color renderColor;

			iPoint temp = currentTile->getTilePos(debugPoint);
			temp.y--;
			int currentGrid = currentTile->LevelsTileMaps[App->scene->currentLevel][temp.y][temp.x];

			if (currentGrid == 0 || currentGrid == 4)
			{
				renderColor = { 0, 255, 0, 200 };
			}
			else
			{
				renderColor = { 255, 0, 0, 200 };
			}

			App->render->AddRectRenderQueue({ 0,0, SCREEN_WIDTH ,SCREEN_HEIGHT }, { 0, 0, 0, 191 });

			App->render->AddRectRenderQueue({ debugPoint.x, debugPoint.y, 16 , 16 }, renderColor);
		}		
	}
	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleDebug::InitDebug(Obstacle** obstacles, Tile* tile)
{
	this->obstacles = obstacles;

	currentTile = tile;

	pauseTimeOffset = 0;
}

void ModuleDebug::ConstructMode()
{
	if(createObject)
	{
		if (App->input->keys[SDL_SCANCODE_BACKSPACE] == KEY_DOWN)
		{
			createObject = false;
		}
	}
	else
	{
		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
		{
			if (arrowPosPointer <= 0) arrowPosPointer = 6;

			else arrowPosPointer--;
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
		{
			if (arrowPosPointer >= 6) arrowPosPointer = 0;

			else arrowPosPointer++;		
		}

		if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
		{
			createObject = true;
			debugPoint = currentTile->getWorldPos({ 1, 2 });
		}

		// temp debug
		if (App->input->keys[SDL_SCANCODE_H] == KEY_DOWN)
		{
			cout << "x: " << debugPoint.x << endl;
			cout << "y: " << debugPoint.y << endl;
		}
	}	
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
