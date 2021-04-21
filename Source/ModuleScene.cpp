#include "ModuleScene.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"
#include "Bomb.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

// Test
#define MAX_OBSTACLES 5

Obstacle* obstacles[MAX_OBSTACLES];
SDL_Texture* texBomb;
SDL_Texture* texStone;
SDL_Texture* texGlassCapsule;
SDL_Texture* texYellowFlower;
SDL_Texture* texItemDestroyed;

Player* bomberman;

ModuleScene::ModuleScene()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
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


	//---------------------------------------------------------------------------------------

	obstacles[0] = new YellowFlower({ 200, 100 }, texYellowFlower, texItemDestroyed);
	//App->obstacles->AddObstacle(*obstacles[1], { 200, 100 }, Type::DESTRUCTABLE_WALL);
	
	obstacles[1] = new GlassCapsule({ 100,100 }, texGlassCapsule);
	//App->obstacles->AddObstacle(*obstacles[0], { 200, 100 }, Type::WALL);

	obstacles[2] = new Stone({ 100, 50 }, texStone);
	//App->obstacles->AddObstacle(*obstacles[2], { 100, 50 }, Type::WALL);

	obstacles[3] = new Bomb({ 50, 50 }, texBomb);
	//App->obstacles->AddObstacle(*obstacles[3], { 50, 50 }, Type::BOMB);
	
	return ret;
}

UpdateResult ModuleScene::Update()
{
	// Update bomebrman
	bomberman->Update();

	// Update obstacle
	for (int i = 0; i < MAX_OBSTACLES; i++)
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
	for (int i = 0; i < MAX_OBSTACLES; i++)
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
	for (uint i = 0; i < MAX_OBSTACLES; ++i)
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
	for (uint i = 0; i < MAX_OBSTACLES; ++i)
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