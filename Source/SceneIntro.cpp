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
	App->audio->PlayMusic("Assets/Audio/Music/INT_MUSIC.ogg", 1.5f);
	Mix_VolumeMusic(10);
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

	//text->showText(App->render->renderer, 50, 50, "Hello world", text->getFonts(80), text->getColors(2));
	//cout << "PostUpdate Scene Intro" << endl;

	return true;
}

bool SceneIntro::CleanUp(bool finalCleanUp)
{
	delete text;
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
