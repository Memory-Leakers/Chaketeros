#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "Tile.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

// Test
#define SCENE_OBSTACLES_NUM 64
#define STONES_NUM 26
#define RED_FLOWER_NUM 4

Obstacle* obstacles[SCENE_OBSTACLES_NUM];
SDL_Texture* texBomb;
SDL_Texture* texStone;
SDL_Texture* texGlassCapsule;
SDL_Texture* texYellowFlower;
SDL_Texture* texItemDestroyed;

Player* bomberman;

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM];

Tile tileMap;

iPoint stonesPos[STONES_NUM], redFlowerPos[RED_FLOWER_NUM];

int tempCounter;

ModuleScene::ModuleScene()
{
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		obstacles[i] = nullptr;
	}
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bomberman = new Player();

	bomberman->Start();

	textmap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	textUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBomb = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	texStone = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	texGlassCapsule = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine.png");
	texYellowFlower = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Yellow_Flower.png");
	texItemDestroyed = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");

	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);


	//----------------OBSTACLE TEST-----------------------------------------------------------

	//obstacles[0] = new YellowFlower({ 200, 100 }, texYellowFlower, texItemDestroyed);
	//
	//obstacles[1] = new GlassCapsule({ 100,100 }, texGlassCapsule);
	//
	//obstacles[2] = new Stone({ 100, 50 }, texStone);

	//obstacles[3] = new Bomb({ 50, 50 }, texBomb);
	
	//PUTS EVERY STONE INTO THE sceneObstacles ARRAY AND SETS stonePos to {0,0}
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{	
		if (tempCounter == STONES_NUM)	//Checks if the last stonePos object is been set to {0,0}
		{
			tempCounter = 0;
			break;	//In that case, there are no more stones to put on the Scene. Therefor, it breaks the loop.
		}
		else if (sceneObstacles[i] == nullptr)	//Checks an empty spot on the sceneObstacles array
		{
			sceneObstacles[i] = new Stone();	//Creates a new Stone on it
			tempCounter++;			//And sets the stonePos position to 0,0 (this is another way of initializing the array. It could be made on another for loop)
		}
	}

	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)	//Same process but with red flowers
	{
		if (tempCounter == RED_FLOWER_NUM)
		{
			tempCounter = 0;
			break;
		}
		else if (sceneObstacles[i] == nullptr)
		{
			//sceneObstacles[i] = new RedFlower();
			redFlowerPos[i] = { 0,0 };
		}
	}
	
	//ITERAION TO LOCATE ALL OBSTACLES POSITION

	for (int i = 0; i < 13; i++)	//Check TileMap y axis
	{
		for (int j = 0; j < 15; j++)	//Check TileMap x axis
		{
			if (tileMap.Level1TileMap[i][j] == 2)	//If a Tile == 2 it is a stone
			{
				for (int k = 0; k < STONES_NUM; k++)	//We iterate through the stonePos array
				{
					if (stonesPos[k].x == 0 && stonesPos[k].y == 0)	//If the stonePos array is empty, we put the Tile located on step 3 on that position
					{
						stonesPos[k] = tileMap.getWorldPos({ j,i }) -= {8, -8};
						break;
					}
				}
			}
			else if (tileMap.Level1TileMap[i][j] == 3)
			{
				for (int k = 0; k < RED_FLOWER_NUM; k++)	//We iterate through the stonePos array
				{
					if (redFlowerPos[k].x == 0 && redFlowerPos[k].y == 0)	//If the stonePos array is empty, we put the Tile located on step 3 on that position
					{
						redFlowerPos[k] = tileMap.getWorldPos({ j,i }) -= {8, -8};
						break;
					}
				}
			}
		}
	}

	for (int j = 0; j < STONES_NUM; j++)
	{
		//App->obstacles->AddObstacle(*sceneObstacles[j], stonesPos[j]);
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
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->Update();
		}	
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	SDL_Rect rectUI =  { 0,0,256,23 };
	
	// Draw Map
	App->render->DrawTexture(textmap, 0, 20, nullptr);

	// Draw Obstacle
	for (int i = 0; i < SCENE_OBSTACLES_NUM; i++)
	{
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->PostUpdate();
		}		
	}

	// Draw Bomberman
	bomberman->PostUpdate();

	// Draw UI
	App->render->DrawTexture(textUI, 0, 0, &rectUI);

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		// cuando se choca algo
		if (obstacles[i] != nullptr && obstacles[i]->getCollider() == c1)
		{
			/*if (obstacles[i]->getType() == Type::DESTRUCTABLE_WALL && c2->type == Type::EXPLOSION)
			{
				obstacles[i]->Die();
				delete obstacles[i];
				obstacles[i] = nullptr;
				break;
			}*/
			// Ejecuta la funcion del cuerpo 1
			obstacles[i]->OnCollision(c2);
		}
	}
}

bool ModuleScene::CleanUp()
{
	LOG("Freeing all test");

	// Liberar obstaculos
	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (obstacles[i] != nullptr)
		{
			//BUG
			//BUG
			//BUG
			//BUG
			//delete test[i];
			delete obstacles[i];
			obstacles[i] = nullptr;
		}
	}

	// Liberar player
	delete bomberman;
	bomberman = nullptr;

	return true;
}