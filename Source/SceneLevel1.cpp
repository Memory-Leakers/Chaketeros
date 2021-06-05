#pragma region Includes

#include "SceneLevel1.h"

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

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"
#include "Timer.h"

#include "ModuleEnemy.h"

#include <time.h>
#include <iostream>
#include <vector>
#include <cstring>

#include "External/SDL_mixer/include/SDL_mixer.h";

#pragma endregion

#pragma region Variables

vector<iPoint> emptySpaces;

NumText sceneUI;

#pragma endregion

SceneLevel1::SceneLevel1()
{
	ID = 4;
}

SceneLevel1::~SceneLevel1()
{
}

void SceneLevel1::InitAssets()
{
	#pragma region Load Sprites

	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Map.png");
	texFG = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/MapEnv.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
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

	#pragma endregion

	#pragma region Init audios

	//Load Sounds
	whistlingSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_WhistlingEndSound.wav");
	oneMinuteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OneMinuteLeft.wav");
	levelCompleteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_LevelCompleteSound.wav");
	extraCoinsBckgSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraCoinsBackgroundSound.wav");

	#pragma endregion
}

void SceneLevel1::CreateScene()
{
	#pragma region Generate Obstacles

	for (int i = 0, k = 0, l = 0, m = 0, n = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			switch (tileMap->LevelsTileMaps[App->scene->currentLevel][i][j])
			{
			case 0:
				emptySpaces.push_back(tileMap->getWorldPos({ j,i }) -= {0, -16});
				break;
			case 2:
				stones[m++] = new Stone(tileMap->getWorldPos({ j,i }) -= {0, -16}, texStone);
				break;
			case 3:
				redFlowerIndex[n++] = k;
				sceneObstacles[k++] = new RedFlower(tileMap->getWorldPos({ j,i }) -= {0, -16}, texEnemies, tileMap);
				break;
			case 6:
				sceneObstacles[k++] = new CoreMecha(tileMap->getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, tileMap, &coreMechaNum);
				break;
			case 10:
				glassCapsuleIndex = k;
				sceneObstacles[k++] = new GlassCapsule(tileMap->getWorldPos({ j,i }) -= {0, -16}, texGlassCapsule);
				break;
			default:
				break;
			}
		}
	}

	#pragma endregion

	cout << endl;

	CreateYellowFlowers();
}

void SceneLevel1::CreateYellowFlowers()
{
	//Randomize yellow flowers number
	yellowFlowersNum = rand() % 6 + 43;
	// Power numbers in this level
	int hasPowerUp = 4;
	// 1 == fire power,  2 == bomb power, 3 == Invensible power
	int powerType[5] = { 0,1,1,2,2 };

	for (int i = 0; i < yellowFlowersNum; ++i)
	{
		int randomNum = rand() % emptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; ++j)
		{
			if (sceneObstacles[j] == nullptr)
			{
				//emptySpaces.at = return value at index
				sceneObstacles[j] = new YellowFlower(emptySpaces.at(randomNum), texYellowFlower, tileMap, powerType[hasPowerUp]);

				//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				iPoint temp = tileMap->getTilePos(emptySpaces.at(randomNum));

				//-1 en Y no sabemos por qu???
				tileMap->LevelsTileMaps[App->scene->currentLevel][temp.y - 1][temp.x] = 5;

				//delete the emptySpace position from the emptySpaces vector
				emptySpaces.erase(emptySpaces.begin() + randomNum);	

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

void SceneLevel1::DebugKeys()
{
	// Player god mod
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
	{
		App->debug->PlayerGodMod(bomberman);
	}

	// Go to GAME OVER with F3
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		App->debug->GameOver();
	}

	// Win
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
	{
		if (!levelComplete)
		{
			App->debug->Win(bomberman, winPosition);
		}
	}

	// Show the powerUps position
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		App->debug->PowerUpPosition();
	}

	// Detect player position in console (use with Q)
	if (App->input->keys[SDL_SCANCODE_F10] == KEY_DOWN)
	{
		App->debug->PlayerPosInConsole(bomberman);
	}

	// Refresh debug tileMap with Q (use with f10)
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_DOWN)
	{
		App->debug->DrawMapInConsole(tileMap, 15, 13);
		App->debug->PrintDebugInformation();
	}

	// Get up flame power
	if (App->input->keys[SDL_SCANCODE_Z] == KEY_DOWN)
	{
		App->debug->AddUpFlame();
	}
}

bool SceneLevel1::Start()
{
	bool ret = true;

	#pragma region Reset Data

	//Reset tileMap
	tileMap = new Tile();

	//Reset variables
	levelComplete = false;

	*sceneObstacles = { nullptr };

	isExtraPointsActive = false;

	coreMechaNum = 2;

	App->scene->currentLevel = 0;

	//	Timer Reset
	timer.Reset();

	isTimeOut = false;

	isChangingScene = false;

	minutes = 4;

	currentSecond = 59;

	totalSeconds = ((int)timer.getDeltaTime() - App->debug->pauseTimeOffset);

	#pragma endregion

	InitAssets();
	
	#pragma region Init Player and Enemies

	// Init player
	bomberman = new Player(tileMap, sceneObstacles);
	bomberman->Start();

	// Spawn enemies
	enemy[3] = new PokaPoka(120, 32, &bomberman->position, tileMap);
	enemy[1] = new Mover({ 168,64 }, texEnemies, &bomberman->pivotPoint, &bomberman->invensibleTime, tileMap);
	enemy[2] = new PokaPoka(120, 192, &bomberman->position, tileMap);
	enemy[0] = new Mover({ 72,160 }, texEnemies, &bomberman->pivotPoint, &bomberman->invensibleTime, tileMap);

	// Init enemies
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		enemy[i]->Start();
	}

	#pragma endregion

	//	Create Scene
	CreateScene();

	// Init debug
	App->debug->InitDebug(sceneObstacles);
	//gameDebug = new Debug(sceneObstacles);

	sceneUI.Start();

	// Create music
	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);

	Mix_VolumeMusic(10);

	App->debug->DrawMapInConsole(tileMap, 15, 13);

	App->debug->PrintDebugInformation();

	return ret;
}

bool SceneLevel1::PreUpdate()
{
	# pragma region PreUpdate & Clean Enemy

	for (int i = 0; i < MAX_ENEMY; ++i)
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
			App->scene->ChangeCurrentScene(SCENE_LEVEL1, 90);
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
			App->scene->playerSettings->isLevelCompleted[0] = true;
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

			else if (!isChangingScene)
			{
				App->scene->ChangeCurrentScene(SCENE_GAMEOVER, 90);
				isChangingScene = true;
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
	
	#pragma region CleanUp & destroy powerUp

	for (int i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr && powerUps[i]->pendingToDelete)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	#pragma endregion	

	//One minute left SFX condition
	if (minutes == 0 && currentSecond == 59)
	{
		App->audio->PlaySound(oneMinuteSFX, 0);
	}

	return true;
}

bool SceneLevel1::Update()
{
	// Special Keys (Debugging)
	DebugKeys();

	#pragma region Bomberman Update

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
				currentSecond = 15;

				timer.Reset();

				totalSeconds = ((int)timer.getDeltaTime() - App->debug->pauseTimeOffset);
			}

			isExtraPointsActive = true;

			bomberman->ExtraPoints = true;

			sceneObstacles[glassCapsuleIndex]->Die();

			CreateCoins();

			for (int i = 0; i < MAX_ENEMY; ++i)
			{
				if (enemy[i] != nullptr)
				{
					enemy[i]->col->pendingToDelete = true;
					delete enemy[i];
					enemy[i] = nullptr;
				}
			}

			for (int i = 0; i < 4; ++i)
			{
				if (sceneObstacles[redFlowerIndex[i]] != nullptr)
				{
					sceneObstacles[redFlowerIndex[i]]->pendingToDelete = true;
					sceneObstacles[redFlowerIndex[i]]->getCollider()->pendingToDelete = true;
				}
			}
		}
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

	#pragma region Update Obstacles and Enemies

	// Update obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->Update();
		}
	}

	//Update Enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Update();
		}
	}

#pragma endregion

	#pragma region Timer Logic (Should be in Update)

	if (!isTimeOut)
	{
		int tempTime = ((int)timer.getDeltaTime() - App->debug->pauseTimeOffset);

		if (tempTime - totalSeconds >= 1)
		{
			currentSecond--;
			totalSeconds = tempTime;
		}
	}

	if (currentSecond == 0)
	{
		if (minutes != 0)
		{
			minutes--;
			timer.Reset();
			totalSeconds = ((int)timer.getDeltaTime() - App->debug->pauseTimeOffset);
			currentSecond = 59;
		}
		else 
		{
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

	return true;
}

bool SceneLevel1::PostUpdate()
{
	#pragma region Drawing

	// Draw Map
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 0, 0);

	//Draw Stone
	for (int i = 0; i < MAX_STONE; ++i)
	{
		if (stones[i] != nullptr)
		{
			stones[i]->PostUpdate();
		}
	}

	// Draw Obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->PostUpdate();
		}
	}

	//Draw Enemy // will be in render exeption
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->PostUpdate();
		}
	}

	//Draw PowerUps
	for (int i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			powerUps[i]->PostUpdate();
		}
	}

	// Draw Player
	if (bomberman != nullptr)
	{
		bomberman->PostUpdate();
	}

	#pragma endregion

	#pragma region DrawUI and Foreground

	// Draw FrontGround
	App->render->AddTextureRenderQueue(texFG, { 0,16 }, nullptr, 1, 100);

	// Draw UI
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 2, 0);

	// Draw CoreMechaUI
	if (coreMechaNum > 0)
	{
		App->render->AddTextureRenderQueue(texMiscUI, { 56, 8 }, &recCoreMehcaUI[0], 2, 1);
	}
	else
	{
		App->render->AddTextureRenderQueue(texMiscUI, { 56, 8 }, &recCoreMehcaUI[1], 2, 1);
	}
	if (coreMechaNum > 1)
	{
		App->render->AddTextureRenderQueue(texMiscUI, { 64, 8 }, &recCoreMehcaUI[0], 2, 1);
	}
	else
	{
		App->render->AddTextureRenderQueue(texMiscUI, { 64, 8 }, &recCoreMehcaUI[1], 2, 1);
	}

	#pragma endregion

	#pragma region Text Drawing

	sceneUI.DrawNum(minutes, { 16,8 });
	sceneUI.DrawNum(currentSecond, { secondsXOffset, 8 });
	sceneUI.DrawNum(App->scene->playerSettings->playerScore, { 144, 8 });
	sceneUI.DrawNum(App->scene->playerSettings->playerLifes, { 232, 8 });

	sceneUI.DrawChar(0, { 25,8 });
	sceneUI.DrawChar(1, { 123,8 });

	#pragma endregion

	// Draw powerUpPos
	App->debug->DrawPowerUpPosition();

	return true;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{
	#pragma region Bomberman Collision

	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->OnCollision(c2);
	}

	#pragma endregion

	#pragma region PowerUps Collision

	for (int i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr && powerUps[i]->getCollider() == c1)
		{
			powerUps[i]->OnCollision(c2);
		}
	}

	#pragma endregion

	#pragma region Obstacle Collision

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

	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (enemy[i] != nullptr && enemy[i]->getCollider() == c1)
		{
			enemy[i]->OnCollision(c2);
		}
	}

#pragma endregion
}

void SceneLevel1::WillCollision(Collider* c1, Collider* c2)
{
	if (bomberman != nullptr && bomberman->col == c1)
	{
		bomberman->WillCollision(c2);
	}
}

void SceneLevel1::CreateCoins()
{
	for (int i = 0, l = 7; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (tileMap->LevelsTileMaps[App->scene->currentLevel][i][j] == 5)
			{
				for (int k = 0; k < yellowFlowersNum; k++)
				{
					if (sceneObstacles[l] != nullptr)
					{
						sceneObstacles[l]->pendingToDelete = true;

						sceneObstacles[l]->powerUp = 0;

						sceneObstacles[l]->getCollider()->pendingToDelete = true;

						iPoint tempPos = sceneObstacles[l]->getPosition();

						l++;
						for (int m = 60; m < SCENE_OBSTACLES_NUM; m++)
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
				tileMap->LevelsTileMaps[App->scene->currentLevel][i][j] = 0;
			}
		}
	}
}

bool SceneLevel1::CleanUp(bool finalCleanUp)
{
	LOG("Freeing all test");

	#pragma region FinalCleanUp

	// Clean Scene if not close the game
	if (!finalCleanUp)
	{
		App->collisions->CleanUpScene();
		App->textures->CleanUpScene();
		App->particle->CleanUpScene();
		App->audio->CleanUpScene();
	}

	#pragma endregion

	#pragma region Delete Stones, Obstacles and PowerUps

	// Delete stone
	for (int i = 0; i < MAX_STONE; ++i)
	{
		if (stones[i] != nullptr)
		{
			delete stones[i];
			stones[i] = nullptr;
		}
	}
	// Delete obstacles
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->CleanUp();
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
	// Delete powerUps
	for (int i = 0; i < 3; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	#pragma endregion

	Mix_HaltMusic();

	//Delete Vector
	emptySpaces.clear();
	emptySpaces.shrink_to_fit();

	#pragma region Delete Player and Enemy

	// Delete player
	if (bomberman != nullptr)
	{
		delete bomberman;
		bomberman = nullptr;
	}

	// Delete Enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->CleanUp();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	#pragma endregion

	// Delete TileMap
	if (tileMap != nullptr)
	{
		delete tileMap;
		tileMap = nullptr;
	}

	return true;
}
