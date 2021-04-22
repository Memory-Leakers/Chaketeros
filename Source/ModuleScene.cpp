#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "Tile.h"
#include "RedFlower.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

// Test
#define SCENE_OBSTACLES_NUM 128

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
Player* bomberman = nullptr;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM] = {nullptr};
Tile tileMap;

ModuleScene::ModuleScene()
{
}

ModuleScene::~ModuleScene()
{
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	// Inicializar jugador
	bomberman = new Player();
	bomberman->Start();

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

	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);

	//Check TileMap y axis
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)	//Check TileMap x axis
		{
			switch (tileMap.Level1TileMap[i][j])
			{
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

	return ret;
}

UpdateResult ModuleScene::Update()
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

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	SDL_Rect rectUI =  { 0,0,256,23 };
	
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

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
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

bool ModuleScene::CleanUp()
{
	LOG("Freeing all test");

	// Liberar obstaculos
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			delete sceneObstacles[i];
			sceneObstacles[i] = nullptr;
		}
	}

	// Liberar player
	delete bomberman;
	bomberman = nullptr;

	return true;
}