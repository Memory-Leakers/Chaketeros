#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleObstacle.h"
#include "YellowFlower.h"
#include "Obstacle.h"

#include "External/SDL_mixer/include/SDL_mixer.h"

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

	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);


	//---------------------------------------------------------------------------------------

<<<<<<< Updated upstream
	//Obstacle* test[10];
	//test[0] = new YellowFlower();
	//App->obstacles->AddObstacle(*test[0], { 200, 100 }, Type::DESTRUCTABLE_WALL);
=======
	//--------------------OBSTACLE TEST-----------------------------
	
	Obstacle* test[10];
	test[0] = new YellowFlower();
	App->obstacles->AddObstacle(*test[0], { 200, 100 }, Collider::Type::DESTRUCTABLE_WALL);
>>>>>>> Stashed changes

	return ret;
}

UpdateResult ModuleScene::Update()
{
	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	return UpdateResult::UPDATE_CONTINUE;
}