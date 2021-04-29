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
	//App->audio->PlayMusic("Assets/Audio/Music/INT_MUSIC.ogg", 1.5f);
	//Mix_VolumeMusic(10);

	image1 = App->textures->Load("Assets/Images/Sprites/IntroSprite/Intro_Image1.png");
	image2 = App->textures->Load("Assets/Images/Sprites/IntroSprite/Intro_Image2.png");

	currentImage = 0;	//Current image displayed

	return true;
}

bool SceneIntro::Update()
{

	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		if (currentImage == 1)
		{
			App->scene->ChangeCurrentScene(MAIN_MENU_SCENE, 120);
		}
		else
		{
			currentImage++;
		}
		
	}

	//cout << "Update Scene Intro" << endl;
	return true;
}

bool SceneIntro::PostUpdate()
{
	cout << "PostUpdate Scene Intro" << endl;

	if (currentImage == 0)
	{

		SDL_Rect temp = { 0,0,512,512 };
		App->render->DrawTextureFreeScaled(image1, { 0,-100 }, 1.5f);
	}
	else 
	{
		App->render->DrawTextureFreeScaled(image2, { 55,20 }, 1.2f);
	}

	//text->showText(App->render->renderer, 50, 50, "Hello world", text->getFonts(80), text->getColors(2));
	//cout << "PostUpdate Scene Intro" << endl;

	return true;
}

bool SceneIntro::CleanUp(bool finalCleanUp)
{
	if (finalCleanUp)
	{
		delete text;
	}
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
