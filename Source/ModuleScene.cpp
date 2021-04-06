#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{
	// Ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// Ship
	ship = { 8, 24, 521, 181 };

	// Flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// L4: TODO 3: Define Girl animation recs
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	stageTexture = App->textures->Load("Assets/ken_stage.png");

	return ret;
}

UpdateResult ModuleScene::Update()
{
	flag.Update();

	// L4: TODO 2: Update ship position (use provided variables)


	// L4: TODO 3: Update girl animation


	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawTexture(stageTexture, 0, 0, &background, 0.75f); // sea and sky
	App->render->DrawTexture(stageTexture, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// L4: TODO 2: Draw the ship from the sprite sheet with some parallax effect

	// L4: TODO 3: Animate the girl on the ship (see sprite sheet)
	
	App->render->DrawTexture(stageTexture, 0, 170, &ground);

	return UpdateResult::UPDATE_CONTINUE;
}