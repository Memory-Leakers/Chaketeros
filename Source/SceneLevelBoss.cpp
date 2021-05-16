#include "SceneLevelBoss.h"

Player* bombermanBoss = nullptr;

SceneLevelBoss::SceneLevelBoss()
{
}

SceneLevelBoss::~SceneLevelBoss()
{
}

void SceneLevelBoss::CreateScene()
{
	// Create new tileMap
	tileMap = new Tile();

	// Create new player
	bombermanBoss = new Player(tileMap);
	bombermanBoss->Start();

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
	texBananacher = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Banana.png");
	texSaru = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Monkey.png");
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/BossMap.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texMiscUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");
}

bool SceneLevelBoss::Start()
{
	// Change current scene
	App->scene->currentLevel = 2;

	InitAssets();

	CreateScene();

	return false;
}

bool SceneLevelBoss::PreUpdate()
{
	return false;
}

bool SceneLevelBoss::Update()
{
	bombermanBoss->Update();

	return false;
}

bool SceneLevelBoss::PostUpdate()
{
	// Draw BG
	App->render->AddTextureRenderQueue(texMap, { 0,0 }, nullptr, 0, 0);

	// Drawu UI bar
	App->render->AddTextureRenderQueue(texUI, { 0,0 }, &recUIbar, 2, 0);

	bombermanBoss->PostUpdate();

	return false;
}

void SceneLevelBoss::OnCollision(Collider* c1, Collider* c2)
{
	bombermanBoss->OnCollision(c2);
}

void SceneLevelBoss::WillCollision(Collider* c1, Collider* c2)
{
	bombermanBoss->WillCollision(c2);
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

	if (bombermanBoss != nullptr)
	{
		delete bombermanBoss;
		bombermanBoss = nullptr;
	}

	return false;
}
