#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"
#include "Tile.h"

#include "External/SDL_mixer/include/SDL_mixer.h"


#define SCENE_OBSTACLES_NUM 64
#define STONES_NUM 26
#define RED_FLOWER_NUM 4

Obstacle* sceneObstacles[SCENE_OBSTACLES_NUM];

Tile tileMap;

iPoint stonesPos[STONES_NUM], redFlowerPos[RED_FLOWER_NUM];

int tempCounter;

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

bool ModuleScene::CleanUp()
{
	LOG("Freeing all test");

	for (uint i = 0; i < SCENE_OBSTACLES_NUM; ++i)
	{
		if (sceneObstacles[i] != nullptr)
		{
			//BUG
			//BUG
			//BUG
			//BUG
			//delete test[i];
			//delete test[i];
			//sceneObstacles[i] = nullptr;
		}
	}

	return true;
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textmap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	textUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");


	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);


	//---------------------------------------------------------------------------------------

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
		App->obstacles->AddObstacle(*sceneObstacles[j], stonesPos[j]);
	}
	
	

/*	sceneObstacles[1] = new YellowFlower();
	App->obstacles->AddObstacle(*sceneObstacles[1], { 200, 100 }, Type::DESTRUCTABLE_WALL);
	

	sceneObstacles[0] = new GlassCapsule();
	App->obstacles->AddObstacle(*sceneObstacles[0], { 200, 100 }, Type::WALL);

	sceneObstacles[2] = new Stone();
	App->obstacles->AddObstacle(*sceneObstacles[2], { 100, 50 }, Type::WALL);

	sceneObstacles[3] = new Bomb({ 50, 50 });
	App->obstacles->AddObstacle(*sceneObstacles[3], { 50, 50 }, Type::BOMB); 
	*/
	return ret;
}

UpdateResult ModuleScene::Update()
{

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	SDL_Rect rectUI =  { 0,0,256,23 };
	
	App->render->DrawTexture(textmap, 0, 20, nullptr);
	App->render->DrawTexture(textUI, 0, 0, &rectUI);
	return UpdateResult::UPDATE_CONTINUE;
}