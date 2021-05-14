#pragma region Includes

#include "SceneLevel1.h"

#include "Collider.h"
#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "Tile.h"
#include "RedFlower.h"
#include "Coin.h"
#include "CoreMecha.h"
#include "PowerUp.h"
#include "PokaPoka.h"
#include "Mover.h"
#include "NumText.h"

#include <time.h>
#include <iostream>
#include <vector>
#include <cstring>

#include "External/SDL_mixer/include/SDL_mixer.h";

#pragma endregion

#pragma region Variables

// Player
Player* bomberman = nullptr;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM] = { nullptr };

NumText sceneUI;

vector<iPoint> emptySpaces;

PowerUp* powerUps[MAX_POWERUPS];

Stone* stones[MAX_STONE];

ModuleEnemy* enemy[MAX_ENEMY];

iPoint winPosition = { 120, 96 };

iPoint powerUpPos[2];

#pragma endregion

//iPoint debugOffset = { 0,0 };

SceneLevel1::SceneLevel1()
{
	// Init random system
	srand(time(NULL));
	score = 0;
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

	#pragma endregion

	#pragma region Init audios

	//Load Sounds
	whistlingSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_WhistlingEndSound.wav");
	oneMinuteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Miscellaneous_Sounds/G_OneMinuteLeft.wav");
	levelCompleteSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Basic_Sounds/G_LevelCompleteSound.wav");
	extraCoinsBckgSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_ExtraCoinsBackgroundSound.wav");

	#pragma endregion
}

void SceneLevel1::PrintDebugInformation()
{
	#pragma region Draw Map in Console
	// Check Map in Console
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			switch (tileMap->Level1TileMap[i][j])
			{
			case -1: cout << "P,"; break;
			case 10: cout << "G,"; break;
			default: cout << tileMap->Level1TileMap[i][j] << ","; break;
			}
		}
		cout << endl;
	}
	#pragma endregion

	#pragma region Manual

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

	#pragma endregion
}

void SceneLevel1::CreateScene()
{
	#pragma region Generate Obstacles

	for (int i = 0, k = 0, l = 0, m = 0, n= 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			switch (tileMap->Level1TileMap[i][j])
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
				//renderExceptionPos[l++] = k;
				sceneObstacles[k++] = new CoreMecha(tileMap->getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, tileMap, &coreMechaNum);
				break;
			case 10:
				//renderExceptionPos[l++] = k;
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
	bool hasPowerUp = true;

	for (int i = 0; i < yellowFlowersNum; ++i)
	{
		if (i >= 2) // Create 2 powerUps
		{
			hasPowerUp = false;
		}

		int randomNum = rand() % emptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; ++j)
		{
			if (sceneObstacles[j] == nullptr)
			{
				sceneObstacles[j] = new YellowFlower(emptySpaces.at(randomNum), texYellowFlower, tileMap, hasPowerUp);	//emptySpaces.at = return value at index

				iPoint temp = tileMap->getTilePos(emptySpaces.at(randomNum));	//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				tileMap->Level1TileMap[temp.y - 1][temp.x] = 5;	//-1 en Y no sabemos por qu???

				emptySpaces.erase(emptySpaces.begin() + randomNum);	//delete the emptySpace position from the emptySpaces vector

				if (hasPowerUp)
				{
					powerUpPos[i] = sceneObstacles[j]->getPosition();
				}

				break;
			}
		}
	}
}

bool SceneLevel1::Start()
{
	LOG("Starting Level 1 Scene");

	bool ret = true;

	#pragma region Reset Data
	//Reset tileMap
	tileMap = new Tile();

	//Reset variables
	App->scene->isLevelCompleted = false;
	*sceneObstacles = { nullptr };
	isExtraPointsActive = false;
	coreMechaNum = 2;

	//	Timer Reset
	timer.Reset();
	isTimeOut = false;
	isChangingScene = false;
	minutes = 4;
	totalSeconds = 59;
	#pragma endregion

	InitAssets();

	#pragma region Init Player and Enemies

	// Init player
	bomberman = new Player(tileMap);
	bomberman->Start();

	// Spawn enemies
	enemy[3] = new PokaPoka(120, 32, &bomberman->position, tileMap);
	enemy[1] = new Mover({ 168,64 }, texEnemies , &bomberman->pivotPoint, tileMap);
	enemy[2] = new PokaPoka(120, 192, &bomberman->position, tileMap);
	enemy[0] = new Mover({ 72,160 }, texEnemies , &bomberman->pivotPoint, tileMap);

	// Init enemies
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		enemy[i]->Start();
	}

	#pragma endregion

	sceneUI.Start();

	// Create music
	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);
	Mix_VolumeMusic(10);

	//	Create Scene
	CreateScene();

	system("cls");
	// Debug information;
	PrintDebugInformation();

	return ret;
}

bool SceneLevel1::PreUpdate()
{
	# pragma region PreUpdate & Clean Enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if (enemy[i] != nullptr)
		{
			if(enemy[i]->pendingToDelete)
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
			App->scene->ChangeCurrentScene(LEVEL1_SCENE, 90, score);
		}
		else
		{
			App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 90, score);
		}
	}
	#pragma endregion

	//One minute left SFX condition
	if (minutes == 0 && currentSecond == 59)
	{
		App->audio->PlaySound(oneMinuteSFX, 0);
	}

	#pragma region Runs out of time Condition
	if (bomberman != nullptr && isTimeOut)
	{
		bomberman->speed = 0;
		if (isExtraPointsActive && !isChangingScene)
		{
			App->audio->PlaySound(whistlingSFX, 0);
			App->scene->ChangeCurrentScene(STAGE_SCENE, 90, score);
			isChangingScene = true;
		}
		else if (!isExtraPointsActive)
		{

			if (App->scene->playerSettings->playerLifes > 0 && !isChangingScene)
			{
				isChangingScene = true;
				App->scene->playerSettings->playerLifes--;
				App->scene->ChangeCurrentScene(LEVEL1_SCENE, 90, score);
			}

			else
			{
				if (!isChangingScene)
				{
					App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 90, score);
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
					if (tileMap->Level1TileMap[l][j] == 8) // if reserved powerUp in this grid
					{
						for (int k = 0; k < MAX_POWERUPS; ++k)
						{
							if (powerUps[k] == nullptr)
							{
								powerUps[k] = new PowerUp(tileMap->getWorldPos({ j,l + 1 }), texPowerUps, texPowerUpDestroyed);
								tileMap->Level1TileMap[l][j] = 0;
								break;
							}

						}
					}
					if (tileMap->Level1TileMap[l][j] == 6)
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

				App->scene->isLevelCompleted = true;
			}

			// CleanUp & destroy pendingToDelete obstacle
			sceneObstacles[i]->CleanUp();
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
	#pragma endregion

	#pragma region CleanUp & destroy powerUp
	for (int i = 0; i < MAX_POWERUPS; i++)
	{
		if (powerUps[i] != nullptr && powerUps[i]->pendingToDelete)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}
	
	#pragma endregion	

	return true;
}

bool SceneLevel1::Update()
{
	#pragma region Special Keys (Debugging)

	#pragma region UI offset debug
	/*if(App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
	{
		debugOffset.y--;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	else if(App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
	{
		debugOffset.y++;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
	{
		debugOffset.x--;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	else if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
	{
		debugOffset.x++;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}*/
	#pragma endregion

	// Go to GAME OVER with F3
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 90, score);
	}

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
	{
		if (!App->scene->isLevelCompleted)
		{
			sceneObstacles[2]->Die();
			sceneObstacles[4]->Die();
			bomberman->position = winPosition;
		}
	}

	// Draw debug tileMap with Q
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_DOWN)
	{
		system("cls");
		cout << endl;
		
		// Debug information
		PrintDebugInformation();
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		debugPowerUp = !debugPowerUp;
	}
	#pragma endregion

	#pragma region Bomberman Update
	if (bomberman != nullptr)
	{
		bomberman->Update();

		// Drop bomb
		if (App->input->keys[SDL_SCANCODE_J] == KEY_DOWN && bomberman->maxBombs > 0)
		{
			for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
			{
				if (sceneObstacles[i] == nullptr)
				{
					sceneObstacles[i] = new Bomb(bomberman, texBomb, tileMap);
					bomberman->maxBombs--;
					break;
				}
			}
		}

		//Check if Player is on the Glass Capsule after completing the level
		if (bomberman->position == winPosition && App->scene->isLevelCompleted && !isExtraPointsActive)
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
		if(enemy[i]!=nullptr)
		{
			enemy[i]->Update();
		}
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

	if (bomberman != nullptr)
	{
		bomberman->PostUpdate();
	}

	#pragma endregion

	#pragma region DrawUI and Foreground
	
	// Draw FrontGround
	//App->render->DrawTexture(texFG, { 0,20 }, nullptr);
	App->render->AddTextureRenderQueue(texFG, { 0,0 }, nullptr, 1, 100);

	// Draw UI
	//App->render->DrawTexture(texUI, 0, 0, &rectUI);
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 2, 0);

	// Draw CoreMechaUI
	if(coreMechaNum > 0)
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

	#pragma region Text Drawing

	sceneUI.DrawNum(minutes, { 16,8 });
	sceneUI.DrawNum(currentSecond, { secondsXOffset, 8 });
	sceneUI.DrawNum(score, { 144, 8 });
	sceneUI.DrawNum(App->scene->playerSettings->playerLifes, { 232, 8 });

	sceneUI.DrawChar(0, { 25,8 });
	sceneUI.DrawChar(1, { 123,8 });
	//text->showText(App->render->renderer, 52, 15, strMinutes , text->getFonts(40), text->getColors((int)textColour::WHITE));
	//text->showText(App->render->renderer, secondsXOffset, 15, strSeconds, text->getFonts(40), text->getColors((int) textColour::WHITE));  //Timer
	//text->showText(App->render->renderer, 360, 15, "SC                    " + strScore, text->getFonts(40), text->getColors((int)textColour::WHITE)); //Points
	//text->showText(App->render->renderer, 695, 15, strLife, text->getFonts(40), text->getColors((int)textColour::WHITE)); //Lifes
	#pragma endregion

	// Draw powerUpPos
	for (int i = 0; i < 2; i++)
	{
		Obstacle* temp = sceneObstacles[7 + i];
		if (debugPowerUp && temp != nullptr && temp->getCollider()->type != Type::BOMB)
		{
			App->render->AddRectRenderQueue({ powerUpPos[i].x + 2,powerUpPos[i].y + 2,12,12 }, { 0,0,255,255 });
		}		
	}

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
	for (int i = 0; i < 3; ++i)
	{
		if (powerUps[i] != nullptr && powerUps[i]->getCollider() == c1)
		{
			powerUps[i]->OnCollision(c2);
		}
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
	for (int i = 0; i < MAX_ENEMY; ++i) {
		// cuando se choca algo
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
			if (tileMap->Level1TileMap[i][j] == 5)
			{
				for (int k = 0; k < yellowFlowersNum; k++)
				{
					if (sceneObstacles[l] != nullptr)
					{
						sceneObstacles[l]->pendingToDelete = true;
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
				tileMap->Level1TileMap[i][j] = 0;
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
	delete bomberman;
	bomberman = nullptr;

	// Delete Enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		if(enemy[i]!=nullptr)
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
