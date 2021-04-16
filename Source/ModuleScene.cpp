#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"

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

	Obstacle* test[10];
	test[1] = new YellowFlower();
	App->obstacles->AddObstacle(*test[1], { 200, 100 }, Type::DESTRUCTABLE_WALL);
	

	test[0] = new GlassCapsule();
	App->obstacles->AddObstacle(*test[0], { 200, 100 }, Type::WALL);
	
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