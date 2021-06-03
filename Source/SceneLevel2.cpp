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
#include "Snail.h"
#include "Mouse.h"

#include "ModuleEnemy.h"


vector<iPoint> level2EmptySpaces;

NumText level2SceneUI;

//TODO: Add PowerUps

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

	for (int i = 0, k = 0, l = 0, m = 0, n = 0; i < 13; ++i)
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
				choreMechaIndex[n++] = k;
				sceneObstacles[k++] = new CoreMecha(level2TileMap->getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, level2TileMap, & coreMechaNum);
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
	yellowFlowersNum = rand() % 6 + 70;
	// Power numbers in this level
	int hasPowerUp = 5;
	// 1 == fire power,  2 == bomb power, 3 == Invensible power
	int powerType[6] = { 0,1,1,2,2,3 };

	for (int i = 0; i < yellowFlowersNum; ++i)
	{
		int randomNum = rand() % level2EmptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; ++j)
		{
			if (sceneObstacles[j] == nullptr)
			{
				//emptySpaces.at = return value at index
				sceneObstacles[j] = new YellowFlower(level2EmptySpaces.at(randomNum), texYellowFlower, level2TileMap, powerType[hasPowerUp]);

				//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				iPoint temp = level2TileMap->getTilePos(level2EmptySpaces.at(randomNum));

				//-1 en Y no sabemos por qu???
				level2TileMap->LevelsTileMaps[App->scene->currentLevel][temp.y - 1][temp.x] = 5;

				//delete the emptySpace position from the emptySpaces vector
				level2EmptySpaces.erase(level2EmptySpaces.begin() + randomNum);

				if (hasPowerUp > 0)
				{
					powerUpPos[i] = sceneObstacles[j]->getPosition();
					hasPowerUp--;
				}

				break;
			}
		}
	}
}

void SceneLevel2::CreateCoins()
{
	for (int i = 0, l = 5; i < 13; ++i)
	{
		for (int j = 0; j < 31; ++j)
		{
			if (level2TileMap->LevelsTileMaps[App->scene->currentLevel][i][j] == 5)
			{
				for (int k = 0; k < yellowFlowersNum; k++)
				{
					if (sceneObstacles[l] != nullptr)
					{
						sceneObstacles[l]->pendingToDelete = true;
						sceneObstacles[l]->getCollider()->pendingToDelete = true;
						sceneObstacles[l]->powerUp = 0;
						iPoint tempPos = sceneObstacles[l]->getPosition();
						l++;
						for (int m = 90; m < SCENE_OBSTACLES_NUM; m++)
						{
							if (sceneObstacles[m] == nullptr)
							{
								sceneObstacles[m] = new Coin(tempPos, texCoin);
								break;
							}
						}
						break;
					}
					else
					{
						l++;
					}
				}
				level2TileMap->LevelsTileMaps[App->scene->currentLevel][i][j] = 0;
			}
		}
	}
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
	texBridge = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/BridgeTogether.png");


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
	levelComplete = false;

	level2SceneUI.Start();

	InitAssets();

	// Init player
	bomberman = new Player(level2TileMap, sceneObstacles);
	bomberman->Start();

	//	Timer Reset
	timer.Reset();
	isTimeOut = false;
	isChangingScene = false;
	minutes = 4;
	totalSeconds = 59;

	isExtraPointsActive = false;

	//Spawn Enemies
	enemy[5] = new Mover(level2TileMap->getWorldPos({ 26,10 }), texEnemies, &bomberman->pivotPoint, level2TileMap);
	enemy[4] = new Mouse(level2TileMap->getWorldPos({ 6,4 }), texEnemies, level2TileMap);
	enemy[3] = new Snail(level2TileMap->getWorldPos({ 13,6 }), texEnemies, level2TileMap);
	enemy[2] = new PokaPoka(424, 32, &bomberman->position, level2TileMap);
	enemy[1] = new Mover(level2TileMap->getWorldPos({ 15,7 }), texEnemies, &bomberman->pivotPoint, level2TileMap);
	enemy[0] = new Mover(level2TileMap->getWorldPos({ 3,7 }), texEnemies, &bomberman->pivotPoint, level2TileMap);

	// Init enemies
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Start();
		}
	}


	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);
	Mix_VolumeMusic(10);

	return false;
}

bool SceneLevel2::PreUpdate()
{
	//	TEMPORAL DEBUG TODO: change to debug class

		// Show the powerUps position
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		debugPowerUp = !debugPowerUp;
	}

# pragma region PreUpdate & Clean Enemy
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->pendingToDelete)
			{
				delete enemy[i];
				enemy[i] = nullptr;
			}
			else
			{
				enemy[i]->PreUpdate();
			}
		}
	}
# pragma endregion

#pragma region Bomberman dies Condition
	if (bomberman != nullptr && bomberman->pendingToDelete)
	{
		delete bomberman;
		bomberman = nullptr;
		if (App->scene->playerSettings->playerLifes > 0)
		{
			App->scene->playerSettings->playerLifes--;
			App->scene->ChangeCurrentScene(SCENE_LEVEL2, 90);
		}
		else
		{
			App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90);
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
			App->scene->ChangeCurrentScene(SCENE_STAGE, 90);
			App->scene->isLevelCompleted[1] = true;
			isChangingScene = true;
		}
		else if (!isExtraPointsActive)
		{

			if (App->scene->playerSettings->playerLifes > 0 && !isChangingScene)
			{
				isChangingScene = true;
				App->scene->playerSettings->playerLifes--;
				App->scene->ChangeCurrentScene(SCENE_LEVEL1, 90);
			}

			else
			{
				if (!isChangingScene)
				{
					App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90);
					isChangingScene = true;
				}

			}
		}
	}
#pragma endregion

#pragma region Clean obstacles

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr && sceneObstacles[i]->pendingToDelete)
		{
#pragma region Create powerUp

			if (sceneObstacles[i]->powerUp != 0)
			{
				for (int k = 0; k < MAX_POWERUPS; ++k)
				{
					if (powerUps[k] == nullptr)
					{
						iPoint tempPos = sceneObstacles[i]->getPosition();
						//tempPos.y++;

						//iPoint tilePos = tileMap->getWorldPos(tempPos);

						powerUps[k] = new PowerUp(tempPos, texPowerUps, texPowerUpDestroyed, sceneObstacles[i]->powerUp);
						//tileMap->LevelsTileMaps[App->scene->currentLevel][tilePos.x][tilePos.y] = 0;
						break;
					}
				}
			}

#pragma endregion

			// Detect if level is complete
			if (coreMechaNum <= 0 && !levelComplete)
			{
				sceneObstacles[glassCapsuleIndex]->Die();

				levelComplete = true;
			}

			// CleanUp & destroy pendingToDelete obstacle
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
#pragma endregion

	//	Clean PowerUps

	for (int i = 0; i < LEVEL2_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			if (powerUps[i]->pendingToDelete)
			{
				delete powerUps[i];
				powerUps[i] = nullptr;
			}
		}
	}

	return false;
}

bool SceneLevel2::Update()
{
	//Debug Keys 

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
	{
		if (!levelComplete)
		{
			for each (int choreMecha in choreMechaIndex)
			{
				if (sceneObstacles[choreMecha] != nullptr)
				{
					sceneObstacles[choreMecha]->getCollider()->pendingToDelete = true;
					delete sceneObstacles[choreMecha];
					sceneObstacles[choreMecha] = nullptr;
				}
			}
			bomberman->position = winPosition;
			levelComplete = true;
			App->render->CameraMove({ 384,0 });
		}
	}


	if (bomberman != nullptr)
	{
		bomberman->Update();
		//Check if Player is on the Glass Capsule after completing the level
		if (bomberman->position == winPosition && levelComplete && !isExtraPointsActive)
		{
			Mix_HaltMusic();
			App->audio->PlaySound(levelCompleteSFX, 0);
			minutes = 0;
			if (currentSecond > 15)
			{
				totalSeconds = 15;

				timer.Reset();
			}
			isExtraPointsActive = true;
			bomberman->ExtraPoints = true;

			sceneObstacles[glassCapsuleIndex]->Die();
			CreateCoins();

			for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
			{
				if (enemy[i] != nullptr)
				{
					enemy[i]->col->pendingToDelete = true;
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}

			if (sceneObstacles[redFlowerIndex] != nullptr)
			{
				sceneObstacles[redFlowerIndex]->getCollider()->pendingToDelete = true;
				delete sceneObstacles[redFlowerIndex];
				sceneObstacles[redFlowerIndex] = nullptr;
			}

		}
	}

#pragma region Timer Logic
	if (!isTimeOut)
	{
		currentSecond = totalSeconds - (int)timer.getDeltaTime();
	}

	if (currentSecond == 0)
	{
		if (minutes != 0)
		{
			minutes--;
			timer.Reset();
		}
		else {
			isTimeOut = true;
		}
	}

	if (currentSecond < 10)
	{
		secondsXOffset = 40;
	}
	else
	{
		secondsXOffset = 32;
	}

#pragma endregion

#pragma region SFX Coins Background 
	// Backgorund sound for Extra points condition
	BGFX_CoinsCounter += timer.Update();

	if (isExtraPointsActive)
	{
		// Check 0.6s
		if (BGFX_CoinsCounter >= 0.6f)
		{
			// Play BG_SFX
			App->audio->PlaySound(extraCoinsBckgSFX, 0);
			// Reset counter
			BGFX_CoinsCounter = 0;
		}
	}
#pragma endregion

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->Update();
		}
	}

	//Update Enemy
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update();
		}
	}

	return false;
}

bool SceneLevel2::PostUpdate()
{
#pragma region Drawing

	// Draw Map
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 0, 0);

	App->render->AddTextureRenderQueue(texBridge, { 258, 96 }, nullptr, 0, 10);

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

	//Draw Enemy // will be in render exeption
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->PostUpdate();
		}
	}

	//	Draw PowerUps

	for (int i = 0; i < LEVEL2_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			powerUps[i]->PostUpdate();
		}
	}

	// Draw UI
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 2, 0);

#pragma region Text Drawing

	level2SceneUI.DrawNum(minutes, { 16,8 });
	level2SceneUI.DrawNum(currentSecond, { secondsXOffset, 8 });
	level2SceneUI.DrawNum(App->scene->playerSettings->playerScore, { 144, 8 });
	level2SceneUI.DrawNum(App->scene->playerSettings->playerLifes, { 232, 8 });

	level2SceneUI.DrawChar(0, { 25,8 });
	level2SceneUI.DrawChar(1, { 123,8 });

#pragma endregion

#pragma endregion

	// Draw powerUpPos
	for (int i = 0; i < LEVEL2_OBSTACLES; i++)
	{
		if (debugPowerUp == true && sceneObstacles[i] != nullptr && sceneObstacles[i]->powerUp != 0)
		{
			App->render->AddRectRenderQueue({ sceneObstacles[i]->getPosition().x + 2,sceneObstacles[i]->getPosition().y + 2,12,12 }, { 0,0,255,255 });

		}
	}

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

#pragma region Enemy Collision
	//Enemy Collision with bomb
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i) {
		// cuando se choca algo
		if (enemy[i] != nullptr && enemy[i]->getCollider() == c1)
		{
			enemy[i]->OnCollision(c2);
		}
	}
#pragma endregion

	//PowerUps Collision

	for (int i = 0; i < LEVEL2_POWERUPS; ++i) {
		// cuando se choca algo
		if (powerUps[i] != nullptr && powerUps[i]->getCollider() == c1)
		{
			powerUps[i]->OnCollision(c2);
		}
	}


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

	// Delete Enemy
	for (int i = 0; i < LEVEL2_MAXENEMIES; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->CleanUp();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
#pragma endregion

	if (level2TileMap != nullptr)
	{
		delete level2TileMap;
		level2TileMap = nullptr;
	}

	for (int i = 0; i < LEVEL2_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	//Delete Vector
	level2EmptySpaces.clear();
	level2EmptySpaces.shrink_to_fit();

	return false;
}


