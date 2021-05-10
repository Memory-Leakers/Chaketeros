#include "SceneSelectStage.h"

#include <iostream>
using namespace std;

SceneSelectStage::SceneSelectStage()
{
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

	#pragma endregion

	for each (StoneCoin stoneCoin in stoneCoins)
	{
		stoneCoin.animation->PushBack({ 2,2,15,16 });
		stoneCoin.animation->PushBack({ 20,2,15,16 });
		stoneCoin.animation->PushBack({ 37,2,15,16 });
		stoneCoin.animation->PushBack({ 56,2,15,16 });
		stoneCoin.animation->PushBack({ 20,23,15,16 });
		stoneCoin.animation->PushBack({ 37,23,15,16 });
		stoneCoin.animation->PushBack({ 56,23,15,16 });
		stoneCoin.animation->speed = 0.3f;
		stoneCoin.animation->loop = true;
		stoneCoin.animation->hasIdle = false;
	}
}

bool SceneSelectStage::Start()
{
	LOG("Load SceneSelectStage");

	InitAssets();

	return true;
}

bool SceneSelectStage::Update()
{
	for each (StoneCoin stoneCoin in stoneCoins)
	{
		stoneCoin.animation->Update();
	}
	return true;
}

bool SceneSelectStage::PostUpdate()
{
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 2, 0);

	SDL_Rect renderRect;
	for each (StoneCoin stoneCoin in stoneCoins)
	{
		renderRect = stoneCoin.animation->GetCurrentFrame();
		App->render->AddTextureRenderQueue(texStoneCoin, stoneCoin.position, &renderRect, 2, 1);
	}
	return true;
}

bool SceneSelectStage::CleanUp(bool finalCleanUp)
{
	LOG("Clean Up SceneSelectStage");
	return true;
}
