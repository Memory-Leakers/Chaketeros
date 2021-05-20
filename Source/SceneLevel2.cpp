#include "SceneLevel2.h"

#include "Application.h"

#include <iostream>

#include "Collider.h"
#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "RedFlower.h"
#include "Coin.h"
#include "CoreMecha.h"
#include "PowerUp.h"
#include "PokaPoka.h"
#include "Mover.h"
#include "NumText.h"
#include "Timer.h"


vector<iPoint> level2EmptySpaces;

SceneLevel2::SceneLevel2()
{
	
	ID = 5;
}

SceneLevel2::~SceneLevel2()
{
}

void SceneLevel2::CreateScene()
{
#pragma region Generate Obstacles

	for (int i = 0, k = 0, l = 0, m = 0; i < 13; ++i)
	{
		for (int j = 0; j < 31; ++j)	//Check TileMap x axis
		{
			switch (level2TileMap->LevelsTileMaps[App->scene->currentLevel][i][j])
			{
			case 0:
				level2EmptySpaces.push_back(level2TileMap->getWorldPos({ j,i }) -= {0, -16});
				break;
			case 1:
			case 2:
				colisionBoxPos = level2TileMap->getWorldPos({ j,i });
				colisionBoxPos.y += 16; // offset

				App->collisions->AddCollider({ colisionBoxPos.x,colisionBoxPos.y,16,16 }, Type::WALL, App->scene);

				break;
			case 3:
				redFlowerIndex = k;
				sceneObstacles[k++] = new RedFlower(level2TileMap->getWorldPos({ j,i }) -= {0, -16}, texEnemies, level2TileMap);
				break;
			case 6:
				sceneObstacles[k++] = new CoreMecha(level2TileMap->getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, level2TileMap, &coreMechaNum);
				break;
			case 10:
				glassCapsuleIndex = k;
				sceneObstacles[k++] = new GlassCapsule(level2TileMap->getWorldPos({ j,i }) -= {0, -16}, texGlassCapsule);
				break;
			default:
				break;
			}
		}
	}
#pragma endregion

	CreateYellowFlowers();
}


void SceneLevel2::CreateYellowFlowers()
{
	//Randomize yellow flowers number
	yellowFlowersNum = rand() % 6 + 60;
	bool hasPowerUp = true;

	for (int i = 0; i < yellowFlowersNum; ++i)
	{
		if (i >= 2) // Create 2 powerUps
		{
			hasPowerUp = false;
		}

		int randomNum = rand() % level2EmptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; ++j)
		{
			if (sceneObstacles[j] == nullptr)
			{
				sceneObstacles[j] = new YellowFlower(level2EmptySpaces.at(randomNum), texYellowFlower, level2TileMap, hasPowerUp);	//emptySpaces.at = return value at index

				iPoint temp = level2TileMap->getTilePos(level2EmptySpaces.at(randomNum));	//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				level2TileMap->LevelsTileMaps[App->scene->currentLevel][temp.y - 1][temp.x] = 5;	//-1 en Y no sabemos por qu???

				level2EmptySpaces.erase(level2EmptySpaces.begin() + randomNum);	//delete the emptySpace position from the emptySpaces vector

				if (hasPowerUp)
				{
					powerUpPos[i] = sceneObstacles[j]->getPosition();
				}

				break;
			}
		}
	}
}

void SceneLevel2::CreateCoins()
{
}

void SceneLevel2::InitAssets()
{
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/MapLevel2.png");
	texFG = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/MapEnv.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texStone = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	texGlassCapsule = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/FragmentsWithMachine.png");
	texYellowFlower = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/YellowFlower.png");
	texEnemies = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");
	texItemDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");
	texPowerUpDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoreMecha = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/CoreMecha.png");
	texPowerUps = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/Powerups.png");
	texMiscUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");
	texBridge = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Bridge.png");


	whistlingSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_WhistlingEndSound.wav");
	oneMinuteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OneMinuteLeft.wav");
	levelCompleteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_LevelCompleteSound.wav");
	extraCoinsBckgSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraCoinsBackgroundSound.wav");

	CreateScene();
}


bool SceneLevel2::Start()
{
	level2TileMap = new Tile();

	App->scene->currentLevel = 1;

	// Init player
	bomberman = new Player(level2TileMap, sceneObstacles);
	bomberman->Start();

	//	Timer Reset
	timer.Reset();
	isTimeOut = false;
	isChangingScene = false;
	minutes = 4;
	totalSeconds = 59;


	InitAssets();

	
	return false;
}

bool SceneLevel2::PreUpdate()
{
	#pragma region Bomberman dies Condition
	if (bomberman != nullptr && bomberman->pendingToDelete)
	{
		delete bomberman;
		bomberman = nullptr;
		if (App->scene->playerSettings->playerLifes > 0)
		{
			App->scene->playerSettings->playerLifes--;
			App->scene->ChangeCurrentScene(SCENE_LEVEL2, 90, score);
		}
		else
		{
			App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90, score);
		}
	}
#pragma endregion

	#pragma region Runs out of time Condition
	if (bomberman != nullptr && isTimeOut)
	{
		bomberman->speed = 0;
		if (isExtraPointsActive && !isChangingScene)
		{
			App->audio->PlaySound(whistlingSFX, 0);
			App->scene->ChangeCurrentScene(SCENE_STAGE, 90, score);
			isChangingScene = true;
		}
		else if (!isExtraPointsActive)
		{

			if (App->scene->playerSettings->playerLifes > 0 && !isChangingScene)
			{
				isChangingScene = true;
				App->scene->playerSettings->playerLifes--;
				App->scene->ChangeCurrentScene(SCENE_LEVEL1, 90, score);
			}

			else
			{
				if (!isChangingScene)
				{
					App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90, score);
					isChangingScene = true;
				}

			}
		}
	}
#pragma endregion

	#pragma region Clean obstacles

		bool anyCoreMecha = false;

		for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
		{
			if (sceneObstacles[i] != nullptr && sceneObstacles[i]->pendingToDelete)
			{
	#pragma region Create powerUp
				for (int l = 0; l < 13; ++l)
				{
					for (int j = 0; j < 15; ++j)
					{
						if (level2TileMap->LevelsTileMaps[App->scene->currentLevel][l][j] == 8) // if reserved powerUp in this grid
						{
							for (int k = 0; k < MAX_POWERUPS; ++k)
							{
								if (powerUps[k] == nullptr)
								{
									powerUps[k] = new PowerUp(level2TileMap->getWorldPos({ j,l + 1 }), texPowerUps, texPowerUpDestroyed);
									level2TileMap->LevelsTileMaps[App->scene->currentLevel][l][j] = 0;
									break;
								}

							}
						}
						if (level2TileMap->LevelsTileMaps[App->scene->currentLevel][l][j] == 6)
						{
							anyCoreMecha = true;
						}
					}
				}
	#pragma endregion

				// Detect if level is complete
				if (!anyCoreMecha && !App->scene->isLevelCompleted)
				{
					sceneObstacles[glassCapsuleIndex]->Die();

					App->scene->isLevelCompleted[1] = true;
				}

				// CleanUp & destroy pendingToDelete obstacle
				delete sceneObstacles[i];
				sceneObstacles[i] = nullptr;
			}
		}
	#pragma endregion

	return false;
}

bool SceneLevel2::Update()
{
	if (bomberman != nullptr)
	{
		bomberman->Update();
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->Update();
		}
	}
	return false;
}

bool SceneLevel2::PostUpdate()
{
#pragma region Drawing

	// Draw Map
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 0, 0);

	// Draw Obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->PostUpdate();
		}
	}

	//	Draw Player
	if (bomberman != nullptr)
	{
		bomberman->PostUpdate();
	}

	// Draw UI
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 2, 0);
	return false;
}

void SceneLevel2::OnCollision(Collider* c1, Collider* c2)
{
	#pragma region Bomberman Collision
	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->OnCollision(c2);
	}
#pragma endregion

	#pragma region Obstacle Collision
		//Obstacle Collision ----------------------
		for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
		{
			// cuando se choca algo
			if (sceneObstacles[i] != nullptr && sceneObstacles[i]->getCollider() == c1)
			{
				sceneObstacles[i]->OnCollision(c2);
			}
		}
	#pragma endregion

}

void SceneLevel2::WillCollision(Collider* c1, Collider* c2)
{
	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->WillCollision(c2);
	}
}

bool SceneLevel2::CleanUp(bool finalCleanUp)
{
	if (!finalCleanUp)
	{
		App->collisions->CleanUpScene();
		App->textures->CleanUpScene();
		App->particle->CleanUpScene();
		App->audio->CleanUpScene();
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}

	if (bomberman != nullptr)
	{
		delete bomberman;
		bomberman = nullptr;
	}

	if (level2TileMap != nullptr)
	{
		delete level2TileMap;
		level2TileMap = nullptr;
	}

	return false;
}


