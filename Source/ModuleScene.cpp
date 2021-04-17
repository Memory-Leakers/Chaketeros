#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "YellowFlower.h"
#include "GlassCapsule.h"
#include "Stone.h"

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

	textmap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");
	textUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");


	//-----------------MUSIC TEST------------------------------------------------------------

	App->audio->PlayMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg", 1.5f);


	//---------------------------------------------------------------------------------------

	Obstacle* test[10];
	test[1] = new YellowFlower();
	App->obstacles->AddObstacle(*test[1], { 200, 100 }, Type::DESTRUCTABLE_WALL);
	

	test[0] = new GlassCapsule();
	App->obstacles->AddObstacle(*test[0], { 200, 100 }, Type::WALL);

	test[2] = new Stone();
	App->obstacles->AddObstacle(*test[2], { 0, 0 }, Type::WALL);
	
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