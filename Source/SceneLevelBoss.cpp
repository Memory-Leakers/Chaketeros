#include "SceneLevelBoss.h"
#include "Bananacher.h"
#include "Saru.h"
#include "NumText.h"
#include "Timer.h"

Player* bombermanBoss = nullptr;
Bananacher* bananacher = nullptr;
Saru* saru = nullptr;
NumText bossText;

SceneLevelBoss::SceneLevelBoss()
{
	ID = 6;
}

SceneLevelBoss::~SceneLevelBoss()
{
}

void SceneLevelBoss::CreateScene()
{
	// Create new tileMap
	tileMap = new Tile();

	// Create new player
	bombermanBoss = new Player(tileMap, obstacles);
	bananacher = new Bananacher({ 120, 64 }, tileMap);
	bombermanBoss->Start();
	bombermanBoss->setPosition(120, 192); //232 352
	saru = new Saru({ 152, 64 }, &bombermanBoss->position, &bananacher->position, tileMap);
	for (int i = 0; i < 13; ++i) //Check TileMap y axis
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			if (tileMap->LevelsTileMaps[2][i][j] == 2)
			{
				iPoint tmpPos = tileMap->getWorldPos({ j,i });
				tmpPos.y += 16; // offset

				App->collisions->AddCollider({ tmpPos.x,tmpPos.y,16,16 }, Type::WALL, App->scene);
			}
		}
	}
}

void SceneLevelBoss::InitAssets()
{
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/BossMap.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texMiscUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");
}

bool SceneLevelBoss::Start()
{
	// Change current scene
	App->scene->currentLevel = 2;

	bossText.Start();

	timer.Reset();

	isTimeOut = false;

	InitAssets();

	CreateScene();

	bananacher->Start();
	saru->Start();

	return false;
}

bool SceneLevelBoss::PreUpdate()
{
	bananacher->PreUpdate();
	saru->PreUpdate();

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr && obstacles[i]->pendingToDelete)
		{
			delete obstacles[i];
			obstacles[i] = nullptr;
		}
	}

	return false;
}

bool SceneLevelBoss::Update()
{

	timer.Update();

#pragma region Timer Logic

	if (minutes == 0 && currentSecond == 0)	//	Time is Out
	{
		isTimeOut = true;
	}


	if (!isTimeOut)
	{
		currentSecond = totalSeconds - (int)timer.getDeltaTime();

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
	}

#pragma endregion


	if (bombermanBoss != nullptr)
	{
		bombermanBoss->Update();
	}

	if (bananacher != nullptr && !bananacher->pendingToDelete)
	{
		bananacher->Update();
		if ((bananacher == nullptr || bananacher->pendingToDelete) && !saruBuff) {
			bananacher->Die();
		}
	}

	/*DELETES BANANACHER in case Saru is playing the death animation*/
	if (bananacher != nullptr && !bananacher->pendingToDelete && saru->getLife() == 1) {
		bananacher->Die();
	}

	if (saru != nullptr && !saru->pendingToDelete ) {
		saru->Update();
		//Checks if bananacher is dead to tigger buff
		if ((bananacher == nullptr || bananacher->pendingToDelete) && !saruBuff) {
			saru->setVRange(20); //Makes saru detect the player on next tile
			saruBuff = true;
		}
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->Update();
		}
	}

	return false;
}

bool SceneLevelBoss::PostUpdate()
{
	// Draw obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->PostUpdate();
		}
	}

	// Draw Bananacher
	if (!bananacher->pendingToDelete)
	{
		bananacher->PostUpdate();
	}

	//Draw Saru
	if (!saru->pendingToDelete) {
		saru->PostUpdate();
	}

	// Draw player
	if (bombermanBoss != nullptr)
	{
		bombermanBoss->PostUpdate();
	}

	// Draw BG
	App->render->AddTextureRenderQueue(texMap, { 0,0 }, nullptr, 0, -10);

	// Draw UI bar
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 0, -5);

	//	Draw Text

	bossText.DrawNum(minutes, { 16,8 }, 3, 0);
	bossText.DrawNum(currentSecond, { secondsXOffset, 8 }, 3, 0);
	bossText.DrawNum(App->scene->playerSettings->playerScore, { 144, 8 }, 3, 0);
	bossText.DrawNum(App->scene->playerSettings->playerLifes, { 232, 8 }, 3, 0);

	bossText.DrawChar(0, { 25,8 }, 0);
	bossText.DrawChar(1, { 123,8 }, 0);

	return false;
}

void SceneLevelBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (bananacher->col == c1)
	{
		bananacher->OnCollision(c2);
	}
	else if (saru->col == c1) {
		saru->OnCollision(c2);
	}
	else if(bombermanBoss->col == c1)
	{
		bombermanBoss->OnCollision(c2);
	}

	else
	{
		for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
		{
			if (obstacles[i] != nullptr && obstacles[i]->getCollider() == c1)
			{
				obstacles[i]->OnCollision(c2);
			}
		}
	}
}

void SceneLevelBoss::WillCollision(Collider* c1, Collider* c2)
{
	if(bombermanBoss->col == c1)
	{
		bombermanBoss->WillCollision(c2);
	}
}

bool SceneLevelBoss::CleanUp(bool finalCleanUp)
{
	if(!finalCleanUp)
	{
		App->collisions->CleanUpScene();
		App->textures->CleanUpScene();
		App->particle->CleanUpScene();
		App->audio->CleanUpScene();
	}

	if (tileMap != nullptr)
	{
		delete tileMap;
		tileMap = nullptr;
	}

	if (bananacher != nullptr)
	{
		delete bananacher;
		bananacher = nullptr;
	}

	if (saru != nullptr) {
		delete saru;
		saru = nullptr;
	}

	if (bombermanBoss != nullptr)
	{
		delete bombermanBoss;
		bombermanBoss = nullptr;
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr)
		{
			delete obstacles[i];
			obstacles[i] = nullptr;
		}
	}

	return false;
}
