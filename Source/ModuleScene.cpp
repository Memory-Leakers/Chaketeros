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

	Mix_Music *music = App->audio->LoadMusic("Assets/Audio/Music/Area1_Jumming_Jungle.ogg");
	Mix_PlayMusic(music, -1);


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