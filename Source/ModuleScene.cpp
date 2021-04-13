#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"

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