#include "SceneMainTitle.h"

#include "Application.h"
#include <string.h>
#include <string>

#include <iostream>
using namespace std;

Timer mainMenuTimer;

FadeInOut* fade;

SceneMainTitle::SceneMainTitle()
{
	ID = 1;
}


SceneMainTitle::~SceneMainTitle()
{
}

bool SceneMainTitle::Start()
{
	#pragma region Textures Setup

	for (int i = 0; i < 9; ++i)
	{
		string temp = ("Assets/Images/Sprites/IntroSprite/GameIntro/IntroImage" + to_string(i+1) + ".png");
		const char* num = temp.c_str();
		introImages[i] = App->textures->Load(num);
	}

	texMainMenu = App->textures->Load("Assets/Images/Sprites/UI_Sprites/MainMenu.png");
	texMenuArrow = App->textures->Load("Assets/Images/Sprites/UI_Sprites/MainMenuArrow.png");
	menuBackgroundRect = { 768, 0, 256, 224 };
	menuStarsBackgroundRect = { 512, 0, 256, 224 };
	menuOptionsRect = { 263, 0, 256, 216 };
	menuTitleRect = { 0,0,256, 200 };
	menuBottomRect = { 48, 200, 144, 8 };

	#pragma endregion

	#pragma region Arrow Positions Setup

	arrowPosition[0] = { 63, 151 };
	arrowPosition[1] = { 63, 167 };
	arrowPosition[2] = { 63, 182 };

	currentArrowPos = &arrowPosition[0];

	#pragma endregion

	changeSelectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_ChangeOptionSound.wav");
	selectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_SelectSound.wav");
	introSFX = App->audio->LoadSound("Assets/Audio/SFX/Intro_Sounds/IntroSFX.wav");

	App->audio->PlaySoundA(introSFX, 0);

	currentImage = 0;
	skipIntro = false;
	mainMenuTimer.Reset();

	fade = FadeInOut::Instance();

	return true;
}

bool SceneMainTitle::Update()
{
	//Update timer and FadeInOut
	mainMenuTimer.Update();
	fade->Update();

	if ((currentImage == 8 && mainMenuTimer.getDeltaTime() >= 1.0f) || skipIntro) 
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_VolumeMusic(30);
			App->audio->PlayMusic("Assets/Audio/Music/TitleScreen.ogg", 0); 
		}

			#pragma region Input Arrow Position Logic

			//Check Input to change Arrow Position
			if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN)
			{
				App->audio->PlaySound(changeSelectSFX, 0);
				if (currentArrowPos == &arrowPosition[2])
				{
					currentArrowPos = &arrowPosition[0];
				}
				else
				{
					currentArrowPos++;
				}
			}
			if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN || App->input->keys[SDL_SCANCODE_W] == KEY_DOWN)
			{
				App->audio->PlaySound(changeSelectSFX, 0);
				if (currentArrowPos == &arrowPosition[0])
				{
					currentArrowPos = &arrowPosition[2];
				}
				else
				{
					currentArrowPos--;
				}
			}

			#pragma endregion

				#pragma region Select Option Logic

				//Select an option based on the arrow position
				if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
				{

					if (currentArrowPos == &arrowPosition[0])
					{
						App->audio->PlaySound(selectSFX, 0);
						App->scene->ChangeCurrentScene(SCENE_AREA, 80);

					}
				}

				#pragma endregion
	}
	else 
	{
		if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN && mainMenuTimer.getDeltaTime() >= 1.0f && fade->currentStep == FadeInOut::FadeSteps::FADE_NONE) 
		{fade->FadeIn(45);}

		if (fade->isFadeInDone == true)
		{
			skipIntro = true;
			Mix_HaltChannel(-1);
			fade->FadeOut(45);
		}

		if (mainMenuTimer.getDeltaTime() >= (4.5f - ((float)currentImage/7.5f)) && currentImage!= 8)
		{
			currentImage++;
			mainMenuTimer.Reset();
		}
	}
	return true;
}

bool SceneMainTitle::PostUpdate()
{
	if ((currentImage == 8 && mainMenuTimer.getDeltaTime() >= 1.0f) || skipIntro)
	{
		//Drawing Textures
		App->render->AddTextureRenderQueue(texMainMenu, { 0,0 }, &menuBackgroundRect, 2, 0);
		App->render->AddTextureRenderQueue(texMainMenu, { 0,0 }, &menuStarsBackgroundRect, 2, 0);
		App->render->AddTextureRenderQueue(texMainMenu, { 0,0 }, &menuTitleRect, 2, 0);
		App->render->AddTextureRenderQueue(texMainMenu, { 0,8 }, &menuOptionsRect, 2, 0);
		App->render->AddTextureRenderQueue(texMainMenu, { 56,200 }, &menuBottomRect, 2, 0);
		App->render->AddTextureRenderQueue(texMenuArrow, *currentArrowPos, nullptr, 2, 0);
	}
	else 
	{
		App->render->AddTextureRenderQueue(introImages[currentImage], { 0,0 }, nullptr, 2);
	}
	return true;
}

bool SceneMainTitle::CleanUp(bool finalCleanUp)
{
	Mix_HaltMusic();
	fade->Release();

	if (!finalCleanUp)
	{
		App->textures->CleanUpScene();
		App->audio->CleanUpScene();
	}

	if (currentArrowPos != nullptr)
	{
		currentArrowPos = nullptr;
	}

	cout << "CleanUp Main Title" << endl;
	return true;
}
