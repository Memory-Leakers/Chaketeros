#include "SceneSelectStage.h"

#include <iostream>
using namespace std;

SceneSelectStage::SceneSelectStage()
{
}

SceneSelectStage::~SceneSelectStage()
{
}

bool SceneSelectStage::Start()
{
	LOG("Load SceneSelectStage");

	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/StageMap.png");
	texStages = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Stages.png");
	texUISelect = App->textures->Load("Assets/Images/Sprites/UI_Sprites/StageSelectUI.png");
	texStoneCoin = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/FragmentsWithoutTheMachine.png");

	return true;
}

bool SceneSelectStage::Update()
{
	//cout << "Update Select Stage" << endl;
	return true;
}

bool SceneSelectStage::PostUpdate()
{
	//cout << "PostUpdate Select Stage" << endl;
	return true;
}

bool SceneSelectStage::CleanUp(bool finalCleanUp)
{
	LOG("Clean Up SceneSelectStage");
	return true;
}
