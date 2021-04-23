#include "SceneIntro.h"

#include "Application.h"

#include <iostream>
using namespace std;


SceneIntro::SceneIntro()
{
}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::Start()
{
	cout << "Start Scene Intro" << endl;
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
	//cout << "PostUpdate Scene Intro" << endl;
	return true;
}

bool SceneIntro::CleanUp(bool finalCleanUp)
{
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
