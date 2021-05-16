#include "SceneIntro.h"

#include "Application.h"

#include <iostream>
using namespace std;

FadeInOut* fadeInOut = nullptr;
Timer introTimer;

SceneIntro::SceneIntro()
{

}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::Start()
{

	#pragma region Load Images

	introImages[0] = App->textures->Load("Assets/Images/Sprites/IntroSprite/Intro_Image1.png");
	introImages[1] = App->textures->Load("Assets/Images/Sprites/IntroSprite/Intro_Image2.png");

	introImages[2] = App->textures->Load("Assets/Images/Sprites/IntroSprite/GameIntro/IntroSegaLogo.png");
	introImages[3] = App->textures->Load("Assets/Images/Sprites/IntroSprite/GameIntro/IntroSegaLogo2.png");


	#pragma endregion
	currentImage = 0;	//Current image displayed
	isChangingScene = false;

	fadeInOut = FadeInOut::Instance();

	return true;
}

bool SceneIntro::Update()
{
	fadeInOut->Update();

	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN && fadeInOut->currentStep == FadeInOut::FadeSteps::FADE_NONE)
	{
		if (currentImage == 3)
		{
			isChangingScene = true;
			App->scene->ChangeCurrentScene(MAIN_MENU_SCENE, 60);
		}
		else
		{
			fadeInOut->FadeIn(30);
		}		
	}
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_DOWN && fadeInOut->currentStep == FadeInOut::FadeSteps::FADE_NONE)
	{
		isChangingScene = true;
		App->scene->ChangeCurrentScene(LEVELBOSS_SCENE, 60);
	}
	if (fadeInOut->isFadeInDone == true)
	{
		currentImage++;

		if(!isChangingScene) fadeInOut->FadeOut(30);
	}

	return true;
}

bool SceneIntro::PostUpdate()
{
	if (currentImage == 0)
	{
		App->render->AddTextureRenderQueue(introImages[0], { 0,-100 }, nullptr, 2, 0, false, 0, 1.5f);
	}
	else if (currentImage == 1)
	{
		App->render->AddTextureRenderQueue(introImages[1], { 55,20 }, nullptr, 2, 0, false, 0, 1.2f);
	}
	else 
	{
		App->render->AddTextureRenderQueue(introImages[currentImage], { 0,0 }, nullptr, 2);
	}

	return true;
}

bool SceneIntro::CleanUp(bool finalCleanUp)
{
	fadeInOut->Release();
	return true;
}
