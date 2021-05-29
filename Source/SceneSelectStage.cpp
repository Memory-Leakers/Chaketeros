#include "SceneSelectStage.h"

#include <iostream>
using namespace std;

// Debug variable
//iPoint debugOffset = { 0,0 };

SceneSelectStage::SceneSelectStage()
{
	ID = 3;

	stoneCoinAnim.PushBack({ 2,2,15,16 });
	stoneCoinAnim.PushBack({ 20,2,15,16 });
	stoneCoinAnim.PushBack({ 37,2,15,16 });
	stoneCoinAnim.PushBack({ 56,2,15,16 });
	stoneCoinAnim.PushBack({ 20,23,15,16 });
	stoneCoinAnim.PushBack({ 37,23,15,16 });
	stoneCoinAnim.PushBack({ 56,23,15,16 });
	stoneCoinAnim.speed = 0.15f;
	stoneCoinAnim.loop = true;
	stoneCoinAnim.hasIdle = false;
}

SceneSelectStage::~SceneSelectStage()
{
}

void SceneSelectStage::InitAssets()
{
	#pragma region Init sprites

	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/StageMap.png");
	texStages = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Stages.png");
	texUISelect = App->textures->Load("Assets/Images/Sprites/UI_Sprites/StageSelectUI.png");
	texStoneCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/FragmentsWithoutTheMachine.png");
	texInGameUI = App->textures->Load("Assets/Images/Sprites/UI_Sprites/InGameUI.png");
	texBigStoneCoins = App->textures->Load("Assets/Images/Sprites/UI_Sprites/BigMoney.png");
	texBomberman = App->textures->Load("Assets/Images/Sprites/Player_Sprites/BombermanSheet.png");

	#pragma endregion
}

bool SceneSelectStage::Start()
{
	LOG("Load SceneSelectStage");

	InitAssets();

	// reset anim
	stoneCoinAnim.Reset();

	stageSelectPointer = 0;

	// determine big money sprite
	bigMoneyPointer = 0;
	for (int i = 0; i < 3; i++)
	{
		if (App->scene->isLevelCompleted[i])
		{
			bigMoneyPointer++;
		}
	}

	return true;
}

void SceneSelectStage::ModifyStagePointer(int mod)
{
	// if key is down
	if (mod == 0)
	{ 
		// show exit icon
		stageSelectPointer = 3;
	}
	else
	{
		// if the last state is Exit
		if (stageSelectPointer == 3)
		{
			// current state should be level 1
			stageSelectPointer = 0;
			return;
		}

		stageSelectPointer += mod;

		// if out of range
		if (stageSelectPointer > 2)
		{
			stageSelectPointer = 0;
		}
		else if (stageSelectPointer < 0)
		{
			stageSelectPointer = 2;
		}

		// go to the next accecible level
		if (stageSelectPointer != 0 && !App->scene->isLevelCompleted[stageSelectPointer - 1])
		{
			ModifyStagePointer(mod);
		}
	}	
}

bool SceneSelectStage::Update()
{
	stoneCoinAnim.Update();

	#pragma region Select Option Logic
	//Select an option based on the arrow position
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		switch (stageSelectPointer)
		{
		case 0: App->scene->ChangeCurrentScene(SCENE_LEVEL1, 60); break;

		case 1: App->scene->ChangeCurrentScene(SCENE_LEVEL2, 60); break;

		case 2: App->scene->ChangeCurrentScene(SCENE_LEVELBOSS, 60); break;

		case 3: App->scene->ChangeCurrentScene(SCENE_AREA, 60); break;

		default: break;
		}
	}
	#pragma endregion

	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
	{
		ModifyStagePointer(0);
	}
	else if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN || App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
	{
		ModifyStagePointer(1);
	}
	else if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
	{
		ModifyStagePointer(-1);
	}

	#pragma region Debug Code
	/*
	if(App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN)
	{
		debugOffset.y--;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN)
	{
		debugOffset.y++;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN)
	{
		debugOffset.x--;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN)
	{
		debugOffset.x++;
		system("cls");
		cout << "X: " << debugOffset.x << "\tY: " << debugOffset.y << endl;
	}
	*/
	#pragma endregion

	return true;
}

bool SceneSelectStage::PostUpdate()
{
	// BG
	App->render->AddTextureRenderQueue(texMap, { 0, 0}, nullptr, 0, 0);

	// BigMoney
	App->render->AddTextureRenderQueue(texBigStoneCoins, { 88, 80 }, &recBigMoney[bigMoneyPointer], 0, 1);

	// Bomberman
	App->render->AddTextureRenderQueue(texBomberman, { 119, 145}, &recBomberman, 1, 0);

	// StageSelectMap
	App->render->AddTextureRenderQueue(texUISelect, { 31, 23}, &recStageSelect[0], 2, 0);

	// StageSelect
	App->render->AddTextureRenderQueue(texUISelect, posStageSelect[stageSelectPointer], &recStageSelect[1], 2, 0);

	// Stage
	App->render->AddTextureRenderQueue(texStages, { 153, 32}, &recStages[stageSelectPointer], 2, 0);

	// InGameUI
	App->render->AddTextureRenderQueue(texInGameUI, { 0, 0 }, &recInGameUI, 2, 0);

	// Coins
	for (int i = 0; i < 3; i++)
	{
		if(!App->scene->isLevelCompleted[i])
		{
			App->render->AddTextureRenderQueue(texStoneCoin, posStoneCoins[i], &stoneCoinAnim.GetCurrentFrame(), 2, 1);
		}
	}

	return true;
}

bool SceneSelectStage::CleanUp(bool finalCleanUp)
{
	if(!finalCleanUp)
	{
		App->textures->CleanUpScene();
	}
	
	LOG("Clean Up SceneSelectStage");
	return true;
}
