#include "SceneIntro.h"

#include "Application.h"

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

	if (App->input->keys[SDL_SCANCODE_T] == KEY_DOWN)
	{
		App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120);
	}

	//cout << "Update Scene Intro" << endl;
	return true;
}

bool SceneIntro::PostUpdate()
{
	cout << "PostUpdate Scene Intro" << endl;

	
	App->render->DrawTexture(textMap, { 0,20 }, nullptr);
	text->showText(App->render->renderer, 50, 50, "Hello world", text->getFonts(80), text->getColors(2));
	//cout << "PostUpdate Scene Intro" << endl;

	return true;
}

bool SceneIntro::CleanUp(bool finalCleanUp)
{
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
