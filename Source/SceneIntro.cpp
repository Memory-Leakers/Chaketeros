#include "SceneIntro.h"

#include <iostream>
using namespace std;


SDL_Texture* textMap = nullptr;

SceneIntro::SceneIntro()
{

}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::Start()
{
	cout << "Start Scene Intro" << endl;

	textMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/map.png");

	return true;
}

bool SceneIntro::Update()
{
	cout << "Update Scene Intro" << endl;
	return true;
}

bool SceneIntro::PostUpdate()
{
	cout << "PostUpdate Scene Intro" << endl;

	
	App->render->DrawTexture(textMap, { 0,20 }, nullptr);


	return true;
}

bool SceneIntro::CleanUp()
{
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
