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

#include "External/SDL_mixer/include/SDL_mixer.h"

// Player
Player* bomberman = nullptr;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM] = { nullptr };

NumText sceneUI;

vector<iPoint> emptySpaces;

PowerUp* powerUps[MAX_POWERUPS];

Stone* stones[MAX_STONE];

ModuleEnemy* enemy[MAX_ENEMY];

iPoint winPosition = { 120, 96 };

SDL_Rect rectUI = { 0,0,256,23 };

SceneLevel1::SceneLevel1()
{
	// Init random system
	srand(time(NULL));
	score = 0;

}

SceneLevel1::~SceneLevel1()
{
}

void SceneLevel1::LoadAsset()
{
	#pragma region Load Sprites

	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	texFG = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/mapEnv.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texStone = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	texGlassCapsule = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine.png");
	texYellowFlower = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Yellow_Flower.png");
	texEnemies = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");
	texItemDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");
	texPowerUpDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoreMecha = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Core_Mecha.png");
	texPowerUps = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/Powerups.png");

	#pragma endregion

	#pragma region Init Particle

	// Explisions General parameter
	explosionCenter = new Particle(500.0f, 0.1f, texBomb);
	explosionMiddle = new Particle(500.0f, 0.1f, texBomb);
	explosionEnd = new Particle(500.0f, 0.1f, texBomb);

	// ExplosionCenter particle
	explosionCenter->anim.PushBack({ 21, 2, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 21, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 40, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 21, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 2, 16, 16 });

	// ExplosionMiddle particle
	explosionMiddle->anim.PushBack({ 42, 2, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 21, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 40, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 21, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 2, 16, 16 });

	// ExplosionEnd particle
	explosionEnd->anim.PushBack({ 62, 2, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 21, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 40, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 21, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 2, 16, 16 });

	// PowerUps destroyed particle
	powerUpDestroyed = new Particle(500.0f, 0.05f, texPowerUpDestroyed);
	powerUpDestroyed->anim.PushBack({ 3,2,26,27 });
	powerUpDestroyed->anim.PushBack({ 35,2,26,27 });
	powerUpDestroyed->anim.PushBack({ 67,2,26,27 });
	powerUpDestroyed->anim.PushBack({ 3,34,26,27 });
	powerUpDestroyed->anim.PushBack({ 35,34,26,27 });
	powerUpDestroyed->anim.PushBack({ 67,34,26,27 });
	powerUpDestroyed->anim.hasIdle = false;

	// Red Flower destroyed particle
	redFlowerDestroyed = new Particle(500.0f, 0.1f, texEnemies);
	redFlowerDestroyed->anim.PushBack({ 2,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 19,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 36,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 52,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 69,133,16,16 });
	redFlowerDestroyed->anim.PushBack({ 86,133,16,16 });

	// Yellow Flower destroyed particle
	yellowFlowerDestroyed = new Particle(500.0f, 0.1f, texYellowFlower);
	yellowFlowerDestroyed->anim.PushBack({ 17,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 33,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 49,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 65,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 81,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 97,0,16,16 });
	yellowFlowerDestroyed->anim.PushBack({ 113,0,16,16 });

	// Mover destroyed particle
	moverDestroyed = new Particle(500.0f, 0.1f, texEnemies);
	moverDestroyed->anim.PushBack({ 232,166,23,30 });

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
				sceneObstacles[k++] = new RedFlower(tileMap->getWorldPos({ j,i }) -= {0, -16}, texEnemies, redFlowerDestroyed, tileMap);
				break;
			case 6:
				renderExceptionPos[l++] = k;
				sceneObstacles[k++] = new CoreMecha(tileMap->getWorldPos({ j,i }) -= {0, -16}, texCoreMecha, texPowerUpDestroyed, powerUpDestroyed, tileMap);
				break;
			case 10:
				renderExceptionPos[l++] = k;
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

	#pragma region Draw Map in Console
	// Check Map in Console
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			cout << tileMap->Level1TileMap[i][j] << ",";
		}
		cout << endl;
	}
	#pragma endregion

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
				sceneObstacles[j] = new YellowFlower(emptySpaces.at(randomNum), texYellowFlower, yellowFlowerDestroyed, tileMap, hasPowerUp);	//emptySpaces.at = return value at index

				iPoint temp = tileMap->getTilePos(emptySpaces.at(randomNum));	//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				tileMap->Level1TileMap[temp.y - 1][temp.x] = 5;	//-1 en Y no sabemos por qu???

				emptySpaces.erase(emptySpaces.begin() + randomNum);	//delete the emptySpace position from the emptySpaces vector

				if(hasPowerUp)
				{
					cout << "PowerUp Pos" << endl;
					cout << "x: " << sceneObstacles[j]->getPosition().x << ", y: " << sceneObstacles[j]->getPosition().y << endl;
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
	isLevelCompleted = false;
	*sceneObstacles = { nullptr };
	isExtraPointsActive = false;

	//	Timer Reset
	timer.Reset();
	isTimeOut = false;
	isChangingScene = false;
	minutes = 4;
	totalSeconds = 59;
	#pragma endregion

	#pragma region Init Player and Enemies
	// Inicializar jugador
	bomberman = new Player(tileMap);
	bomberman->Start();

	//	Spawn enemies
	enemy[3] = new PokaPoka(200, 160, &bomberman->position, tileMap);
	enemy[1] = new Mover({ 168,64 }, &bomberman->position, tileMap);
	enemy[2] = new PokaPoka(200, 160, &bomberman->position, tileMap);
	enemy[0] = new Mover({ 72,160 }, &bomberman->position, tileMap);

	//Start Enemy
	for (int i = 0; i < MAX_ENEMY; ++i)
	{
		enemy[i]->Start();
	}

#pragma endregion


	LoadAsset();

	sceneUI.Start();

	// Create music
	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);
	Mix_VolumeMusic(10);

	//	Create Scene
	CreateScene();

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
		if (playerLifes > 0)
		{
			playerLifes--;
			App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120, score);
		}
		else
		{
			App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 120, score);
			playerLifes = 3;
		}
	}
	#pragma endregion

	//One minute left SFX condition
	if (minutes == 0 && currentSecond == 59)
	{
		App->audio->PlaySound(SFX::ONE_MINUTE_LEFT_SFX, 0);
	}

	#pragma region Runs out of time Condition
	if (bomberman != nullptr && isTimeOut)
	{
		if (isExtraPointsActive && !isChangingScene)
		{
			App->audio->PlaySound(SFX::END_WHISTLING_SFX, 0);
			App->scene->ChangeCurrentScene(MAIN_MENU_SCENE, 120, score);
			isChangingScene = true;
		}
		else if (!isExtraPointsActive)
		{

			bomberman->speed = 0;
			if (playerLifes > 0 && !isChangingScene)
			{
				isChangingScene = true;
				playerLifes--;
				App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120, score);
			}

			else
			{
				if (!isChangingScene)
				{
					App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 120, score);
					isChangingScene = true;
					playerLifes = 3;
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
								powerUps[k] = new PowerUp(tileMap->getWorldPos({ j,l + 1 }), texPowerUps, powerUpDestroyed);
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
			if (!anyCoreMecha && !isLevelCompleted)
			{
				sceneObstacles[glassCapsuleIndex]->Die();
				isLevelCompleted = true;
			}

			// CleanUp & destroy pendingToDelete obstacle
			sceneObstacles[i]->CleanUp();
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}
	#pragma endregion

	#pragma region CleanUp & destroy powerUp
	if (powerUps[0] != nullptr && powerUps[0]->pendingToDelete)
	{
		delete powerUps[0];
		powerUps[0] = nullptr;
	}
	#pragma endregion	

	return true;
}

bool SceneLevel1::Update()
{
	#pragma region Special Keys (Debugging)
	// Go to GAME OVER with F3
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
	{
		App->scene->ChangeCurrentScene(GAME_OVER_SCENE, 120, score);
	}

	// Cout Score in console with C
	if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN)
	{
		cout << "Score: " << score << endl;
	}

	// Draw debug tileMap with Q
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_DOWN)
	{
		system("cls");
		cout << endl;
		// Check Map in Console
		for (int i = 0, k = 0; i < 13; ++i)
		{
			for (int j = 0; j < 15; ++j)
			{
				if (tileMap->Level1TileMap[i][j] == -1)
				{
					cout << "P,";
				}
				else
				{
					cout << tileMap->Level1TileMap[i][j] << ",";
				}
			}
			cout << endl;
		}
		//sceneObstacles[glassCapsuleIndex]->Die();
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
					sceneObstacles[i] = new Bomb(bomberman, texBomb, explosionCenter, explosionMiddle, explosionEnd, tileMap);
					bomberman->maxBombs--;
					break;
				}
			}
		}

		//Check if Player is on the Glass Capsule after completing the level
		if (bomberman->position == winPosition && isLevelCompleted && !isExtraPointsActive)
		{
			Mix_HaltMusic();
			App->audio->PlaySound(SFX::LEVEL_COMPLETE_SFX, 0);
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

			
			
			for (int i = 0; i < 4; ++i)
			{
				if (sceneObstacles[redFlowerIndex[i]] != nullptr)
				{
					sceneObstacles[redFlowerIndex[i]]->pendingToDelete = true;
					sceneObstacles[redFlowerIndex[i]]->getCollider()->pendingToDelete = true;
				}
			}
			if (currentSecond == 0) {
				App->audio->PlaySound(SFX::LEVEL_COMPLETE_SFX, 0);
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
			App->audio->PlaySound(SFX::EXTRA_COINS_BCKGR_SFX, 0);
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

	// Draw Map
	//App->render->DrawTexture(texMap, { 0, 16 }, nullptr);


	return true;

}

bool SceneLevel1::PostUpdate()
{
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 0);

	#pragma region Drawing

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

	#pragma endregion

	#pragma region RenderExeption
	// Get renderExpion
	int ExeptionRenderOrder[4][2];

	for (int i = 0; i < 3; ++i)
	{
		if (sceneObstacles[renderExceptionPos[i]] != nullptr)
		{
			ExeptionRenderOrder[i][0] = i;
			ExeptionRenderOrder[i][1] = sceneObstacles[renderExceptionPos[i]]->getPosition().y;
		}
		else
		{
			ExeptionRenderOrder[i][0] = -1;
		}
	}

	// Sort render exeption
	ExeptionRenderOrder[3][0] = 3;
	if (bomberman != nullptr)
	{
		ExeptionRenderOrder[3][1] = bomberman->position.y;
	}

	int temp = 0;
	int tempArr[] = { ExeptionRenderOrder[0][0],ExeptionRenderOrder[0][1] };

	for (int j = 0; j < 3; ++j)
	{
		memcpy(tempArr, ExeptionRenderOrder[j], sizeof(ExeptionRenderOrder[j]));
		temp = j;
		for (int i = j; i < 4; ++i)
		{
			if (ExeptionRenderOrder[i][1] < tempArr[1])
			{
				memcpy(ExeptionRenderOrder[temp], ExeptionRenderOrder[i], sizeof(ExeptionRenderOrder[i]));
				memcpy(ExeptionRenderOrder[i], tempArr, sizeof(tempArr));
				memcpy(tempArr, ExeptionRenderOrder[temp], sizeof(ExeptionRenderOrder[temp]));
				temp = i;
			}
		}
	}


	//Render exeptions
	for (int i = 0; i < 4; ++i)
	{
		if (ExeptionRenderOrder[i][0] != -1)
		{
			if (ExeptionRenderOrder[i][0] == 3)
			{
				if (bomberman != nullptr)
				{
					bomberman->PostUpdate();
				}
			}
			else
			{
				if (sceneObstacles[renderExceptionPos[ExeptionRenderOrder[i][0]]] != nullptr)
				{
					sceneObstacles[renderExceptionPos[ExeptionRenderOrder[i][0]]]->PostUpdate();
				}
			}
		}
	}

	// Render PowerUp
	for (int i = 0; i < 3; ++i)
	{

		if (powerUps[i] != nullptr)
		{
			powerUps[i]->PostUpdate();
		}

	}
	#pragma endregion

	#pragma region DrawUI and Foreground
	
	// Draw FrontGround
	//App->render->DrawTexture(texFG, { 0,20 }, nullptr);
	App->render->AddTextureRenderQueue(texFG, { 0,0 }, nullptr, 2);

	// Draw UI
	//App->render->DrawTexture(texUI, 0, 0, &rectUI);
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &rectUI, 2);

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
	sceneUI.DrawNum(score, { 160, 8 });
	sceneUI.DrawNum(playerLifes, { 232, 8 });

	sceneUI.DrawChar(0, { 25,8 });
	sceneUI.DrawChar(1, { 123,8 });
	//text->showText(App->render->renderer, 52, 15, strMinutes , text->getFonts(40), text->getColors((int)textColour::WHITE));
	//text->showText(App->render->renderer, secondsXOffset, 15, strSeconds, text->getFonts(40), text->getColors((int) textColour::WHITE));  //Timer
	//text->showText(App->render->renderer, 360, 15, "SC                    " + strScore, text->getFonts(40), text->getColors((int)textColour::WHITE)); //Points
	//text->showText(App->render->renderer, 695, 15, strLife, text->getFonts(40), text->getColors((int)textColour::WHITE)); //Lifes
	#pragma endregion

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
	}
	else
	{
		delete text;
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

	delete tileMap;
	tileMap = nullptr;

	//Delete Vector
	emptySpaces.clear();
	emptySpaces.shrink_to_fit();

	#pragma region Delete Particles
	// Delete particles
	delete explosionCenter;
	explosionCenter = nullptr;
	delete explosionMiddle;
	explosionMiddle = nullptr;
	delete explosionEnd;
	explosionEnd = nullptr;
	delete powerUpDestroyed;
	powerUpDestroyed = nullptr;
	delete redFlowerDestroyed;
	redFlowerDestroyed = nullptr;
	delete yellowFlowerDestroyed;
	yellowFlowerDestroyed = nullptr;
	delete yellowFlowerDestroyed;
	delete moverDestroyed;
	moverDestroyed = nullptr;
	#pragma endregion

	#pragma region Delete Player and Enemy
	// Delete player
	delete bomberman;
	bomberman = nullptr;

	//Delete Enemy
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

	return true;
}
