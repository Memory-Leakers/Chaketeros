#include "SceneSelectArea.h"

#include <iostream>
using namespace std;
#include "Application.h"

Timer particleTime;

SceneSelectArea::SceneSelectArea()
{
	// Animation should be init in constructor!!!!
	#pragma region Init Anim

// Level 1 Cheese Animation
	texLevel1CheeseAnim.PushBack({ 0,0,39,48 });
	texLevel1CheeseAnim.PushBack({ 64,0,39,48 });
	texLevel1CheeseAnim.PushBack({ 128,0,39,48 });
	texLevel1CheeseAnim.speed = 0.05f;
	texLevel1CheeseAnim.hasIdle = false;
	texLevel1CheeseAnim.loop = true;
	// Level 2 Cheese Animation
	texLevel2CheeseAnim.PushBack({ 0,256,40,51 });
	texLevel2CheeseAnim.PushBack({ 64,256,40,51 });
	texLevel2CheeseAnim.speed = 0.05f;
	texLevel2CheeseAnim.hasIdle = false;
	texLevel2CheeseAnim.loop = true;
	// Level 3 Cheese Animation
	texLevel3CheeseAnim.PushBack({ 0,192,48,45 });
	texLevel3CheeseAnim.PushBack({ 64,192,48,45 });
	texLevel3CheeseAnim.speed = 0.05f;
	texLevel3CheeseAnim.hasIdle = false;
	texLevel3CheeseAnim.loop = true;
	// Level 4 Cheese Animation
	texLevel4CheeseAnim.PushBack({ 0,128,40,52 });
	texLevel4CheeseAnim.PushBack({ 64,128,40,52 });
	texLevel4CheeseAnim.speed = 0.05f;
	texLevel4CheeseAnim.hasIdle = false;
	texLevel4CheeseAnim.loop = true;
	// Level 5 Cheese Animation
	texLevel5CheeseAnim.PushBack({ 0,64,40,47 });
	texLevel5CheeseAnim.PushBack({ 64,64,40,47 });
	texLevel5CheeseAnim.speed = 0.05f;
	texLevel5CheeseAnim.hasIdle = false;
	texLevel5CheeseAnim.loop = true;
#pragma endregion
}

SceneSelectArea::~SceneSelectArea()
{
}

bool SceneSelectArea::Start()
{
	cout << "Start Select Area" << endl;
	//Music
	Mix_VolumeMusic(15);
	App->audio->PlayMusic("Assets/Audio/Music/AreaSelect.ogg", 1.5f);

	#pragma region Textures and Animations Setup
	texSelectArea = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Area.png");
	texMainMenu = App->textures->Load("Assets/Images/Sprites/UI_Sprites/MainMenu.png");
	texLevels = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Levels.png");
	texbombermaninArea = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png");
	BombermaninAreaRect = { 49,50, 15 ,20 };
	SelectStageBackgroundRect = { 256, 0, 256, 224 };
	StageCheeseandStarsRect = { 512,6,256,224 };
	UIStageLevel1Rect = { 0, 0, 256, 224 };
	UIStageLevel2Rect = { 0, 224, 256, 224 };
	#pragma endregion

	#pragma region Arrow Positions Setup
	arrowLevelPosition[0] = { 129, 77 };
	arrowLevelPosition[1] = { 130, 108 };
	arrowLevelPosition[2] = { 127, 124 };
	arrowLevelPosition[3] = { 90, 110 };
	arrowLevelPosition[4] = { 92, 76 };

	currentArrowLevelPos = &arrowLevelPosition[0];
	#pragma endregion

	changeSelectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_ChangeOptionSound.wav");
	selectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_SelectSound.wav");

	#pragma region reset anim
	texLevel1CheeseAnim.Reset();
	texLevel2CheeseAnim.Reset();
	texLevel3CheeseAnim.Reset();
	texLevel4CheeseAnim.Reset();
	texLevel5CheeseAnim.Reset();
	#pragma endregion

	starParticle = new Particle(200.0f, 0.2f, texMainMenu);

	starParticle->anim.PushBack({ 608, 200, 1, 1 });
	starParticle->anim.PushBack({ 608, 201, 1, 1 });
	starParticle->anim.loop = true;

	return true;
}

bool SceneSelectArea::Update()
{
	
	particleTime.Update();

	if(particleTime.getDeltaTime() > 0.15f)
	{
		particleTime.Reset();
		int sig[2] = { 1,-1 };

		for (int i = 0; i < 3; i++)
		{
			starParticle->setSpeed({ (rand() % 3 + 1) * sig[rand() % 2], (rand() % 3 + 1) * sig[rand() % 2] });
			App->particle->AddParticle(*starParticle, 128, 120, Type::NONE);
		}
	}

	cout << "Update Select Area" << endl;
	// Animations Update
	texLevel1CheeseAnim.Update();
	texLevel2CheeseAnim.Update();
	texLevel3CheeseAnim.Update();
	texLevel4CheeseAnim.Update();
	texLevel5CheeseAnim.Update();

	#pragma region Input Arrow Position Logic
	//Check Input to change Arrow Position
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		if (currentArrowLevelPos == &arrowLevelPosition[5])
		{
			currentArrowLevelPos = &arrowLevelPosition[0];
		}
		else
		{
			currentArrowLevelPos++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN || App->input->keys[SDL_SCANCODE_W] == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		if (currentArrowLevelPos == &arrowLevelPosition[0])
		{
			currentArrowLevelPos = &arrowLevelPosition[5];
		}
		else
		{
			currentArrowLevelPos--;
		}
	}
	#pragma endregion

	#pragma region Select Option Logic
	//Select an option based on the arrow position
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		if (currentArrowLevelPos == &arrowLevelPosition[0])
		{
			App->audio->PlaySound(selectSFX, 0);
			App->scene->ChangeCurrentScene(STAGE_SCENE, 80);
		}
	}
	#pragma endregion

	if (App->scene->isLevelCompleted == true) 
	{	
		Completed();
	}

	

	return true;
}

bool SceneSelectArea::PostUpdate()
{
	cout << "PostUpdate Select Area" << endl;

	App->render->AddTextureRenderQueue(texSelectArea, { 0,0 }, &SelectStageBackgroundRect, 0,0);

	App->render->AddTextureRenderQueue(texMainMenu, { 0,-6 }, &StageCheese1Completed, 2, 0);

	App->render->AddTextureRenderQueue(texbombermaninArea, { 165, 52 }, &BombermaninAreaRect, 2, 1);
	if (currentArrowLevelPos == &arrowLevelPosition[0]) {
		App->render->AddTextureRenderQueue(texSelectArea, { 0,0 }, &UIStageLevel1Rect, 2, 2);
	}
	else {
		App->render->AddTextureRenderQueue(texSelectArea, { 0,0 }, &UIStageLevel2Rect, 2, 2);
	}
	if (App->scene->isLevelCompleted == false) 
	{
		App->render->AddTextureRenderQueue(texLevels, { 136, 58 }, &texLevel1CheeseAnim.GetCurrentFrame(), 2, 3);
	}
	App->render->AddTextureRenderQueue(texLevels, { 141, 108 }, &texLevel2CheeseAnim.GetCurrentFrame(), 2, 4);
	App->render->AddTextureRenderQueue(texLevels, { 103, 134 }, &texLevel3CheeseAnim.GetCurrentFrame(), 2, 7);
	App->render->AddTextureRenderQueue(texLevels, { 73, 107 }, &texLevel4CheeseAnim.GetCurrentFrame(), 2, 6);
	App->render->AddTextureRenderQueue(texLevels, { 79, 60 }, &texLevel5CheeseAnim.GetCurrentFrame(), 2, 5);

	/*App->render->AddTextureRenderQueue(texLevels, { 127, 73 }, &texLevel1CheeseAnim.GetCurrentFrame(), 2,3);
	App->render->AddTextureRenderQueue(texLevels, { 128, 105 }, &texLevel2CheeseAnim.GetCurrentFrame(), 2,4);
	App->render->AddTextureRenderQueue(texLevels, { 104, 122 }, &texLevel3CheeseAnim.GetCurrentFrame(), 2,7);
	App->render->AddTextureRenderQueue(texLevels, { 88, 106 }, &texLevel4CheeseAnim.GetCurrentFrame(), 2, 6);
	App->render->AddTextureRenderQueue(texLevels, { 88, 75 }, &texLevel5CheeseAnim.GetCurrentFrame(), 2, 5);*/
	return true;
}

bool SceneSelectArea::CleanUp(bool finalCleanUp)
{
	cout << "CleanUp Select Area" << endl;
	if (!finalCleanUp)
	{
		App->textures->CleanUpScene();
		App->audio->CleanUpScene();
		App->particle->CleanUpScene();
	}

	if (starParticle != nullptr)
	{
		delete starParticle;
		starParticle = nullptr;
	}

	return true;
}

void SceneSelectArea::Completed()
{
	App->render->AddTextureRenderQueue(texLevels, { 127, 73 }, &texLevel1CheeseAnim.GetCurrentFrame(), 2, 3);
}
