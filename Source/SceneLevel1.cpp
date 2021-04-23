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

#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

#include "External/SDL_mixer/include/SDL_mixer.h"

//textura mapa
SDL_Texture* texMap = nullptr;
SDL_Texture* texFG = nullptr;
//Textura UI 
SDL_Texture* texUI = nullptr;

SDL_Texture* texBomb = nullptr;
SDL_Texture* texStone = nullptr;
SDL_Texture* texGlassCapsule = nullptr;
SDL_Texture* texYellowFlower = nullptr;
SDL_Texture* texRedFlower = nullptr;
SDL_Texture* texItemDestroyed = nullptr;
SDL_Texture* texCoin = nullptr;
SDL_Texture* texDie = nullptr;
Player* bomberman = nullptr;

// Particle
//Template particle for an center of explosion
Particle* explosionCenter = nullptr;

//Template particle for an middle of explosion
Particle* explosionMiddle = nullptr;

//Template particle for an end of explosion
Particle* explosionEnd = nullptr;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM] = { nullptr };
vector<iPoint> emptySpaces;
int yellowFlowers;
Tile tileMap;

SceneLevel1::SceneLevel1()
{
	srand(time(NULL));
}

SceneLevel1::~SceneLevel1()
{
}

void SceneLevel1::LoadAsset()
{
	// Cargar sprites
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	texFG = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/mapEnv.png");
	texUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texStone = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	texGlassCapsule = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine.png");
	texYellowFlower = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Yellow_Flower.png");
	texRedFlower = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");
	texItemDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");
	texCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");
	texDie = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Coins.png");

	#pragma region Init Explosion Particle

	// General parameter
	explosionCenter = new Particle(true, 500.0f, 0.01f, texBomb);
	explosionMiddle = new Particle(true, 500.0f, 0.01f, texBomb);
	explosionEnd = new Particle(true, 500.0f, 0.01f, texBomb);

	// ExplosionCenter particle
	explosionCenter->anim.PushBack({ 21, 2, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 21, 16, 16 });
	explosionCenter->anim.PushBack({ 21, 40, 16, 16 });

	// ExplosionMiddle particle
	explosionMiddle->anim.PushBack({ 42, 2, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 21, 16, 16 });
	explosionMiddle->anim.PushBack({ 42, 40, 16, 16 });	

	// ExplosionEnd particle
	explosionEnd->anim.PushBack({ 62, 2, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 21, 16, 16 });
	explosionEnd->anim.PushBack({ 62, 40, 16, 16 });

#pragma endregion
}

bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	// Inicializar jugador
	bomberman = new Player();
	bomberman->Start();

	//Randomize yellow flowers number
	yellowFlowers = rand() % 6 + 43;

	LoadAsset();

	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);

	//Check TileMap y axis
	//sceneObstacles[0] = new Bomb({ 100,100 }, texBomb, explosionCenter, explosionMiddle, explosionEnd);
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			switch (tileMap.Level1TileMap[i][j])
			{
			case 0:
				emptySpaces.push_back(tileMap.getWorldPos({ j,i }) -= {8, -8});
				break;
			case 2:
				sceneObstacles[k++] = new Stone(tileMap.getWorldPos({ j,i }) -= {8, -8}, texStone);
				break;
			case 3:
				sceneObstacles[k++] = new RedFlower(tileMap.getWorldPos({ j,i }) -= {8, -8}, texRedFlower);
				break;
			case 9:
				sceneObstacles[k++] = new GlassCapsule(tileMap.getWorldPos({ j,i }) -= {8, -8}, texGlassCapsule);
				break;
			default:
				break;
			}
		}
	}

	CreateYellowFlowers();

	return ret;
}

bool SceneLevel1::Update()
{

	// Update bomebrman
	bomberman->Update();

	// Update obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->Update();
		}
	}

	return true;
}

bool SceneLevel1::PostUpdate()
{
	SDL_Rect rectUI = { 0,0,256,23 };

	// Draw Map
	App->render->DrawTexture(texMap, { 0,20 }, nullptr);

	// Draw Obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (sceneObstacles[i] != nullptr)
		{
			sceneObstacles[i]->PostUpdate();

			// Si hay obstaculo que ubica arriba de player o player esta en primera fila
			if (sceneObstacles[i]->getPosition().y <= bomberman->position.y || bomberman->position.y < 48) // Pendiente de optimizar
			{
				// Draw Bomberman
				bomberman->PostUpdate();
			}
		}
	}

	// Draw FrontGround
	App->render->DrawTexture(texFG, { 0,20 }, nullptr);

	// Draw UI
	App->render->DrawTexture(texUI, 0, 0, &rectUI);

	return true;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		// cuando se choca algo
		if (sceneObstacles[i] != nullptr && sceneObstacles[i]->getCollider() == c1)
		{
			sceneObstacles[i]->OnCollision(c2);
		}
	}
}

bool SceneLevel1::CleanUp()
{
	LOG("Freeing all test");

	// Delete obstacles
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}

	// Delete particles
	delete explosionCenter;
	delete explosionMiddle;
	delete explosionEnd;

	// Delete player
	delete bomberman;
	bomberman = nullptr;

	return true;
}

void SceneLevel1::CreateYellowFlowers()
{
	for (int i = 0; i < yellowFlowers; i++)
	{
		int randomNum = rand() % emptySpaces.size();
		for (int j = 0; j < SCENE_OBSTACLES_NUM; j++)
		{
			if (sceneObstacles[j] == nullptr)
			{
				sceneObstacles[j] = new YellowFlower(emptySpaces.at(randomNum), texYellowFlower, texDie);	//emptySpaces.at = return value at index

				iPoint temp = tileMap.getTilePos(emptySpaces.at(randomNum));	//Sets tileMap position to 4 to prevent multiple flowers on the same tile
				tileMap.Level1TileMap[temp.y][temp.x] = 4;

				emptySpaces.erase(emptySpaces.begin() + randomNum);		//delete the emptySpace position from the emptySpaces vector

				break;
			}
		}
	}
}
