#include "SceneMainTitle.h"

#include "Application.h"

#include <iostream>
using namespace std;

SceneMainTitle::SceneMainTitle()
{
}

SceneMainTitle::~SceneMainTitle()
{
}

bool SceneMainTitle::Start()
{
	Mix_VolumeMusic(15);
	App->audio->PlayMusic("Assets/Audio/Music/TitleScreen.ogg", 1.5f);

	texMainMenu = App->textures->Load("Assets/Images/Sprites/UI_Sprites/MainMenu.png");
	texMenuArrow = App->textures->Load("Assets/Images/Sprites/UI_Sprites/MainMenuArrow.png");
	menuBackgroundRect = { 768, 0, 256, 224 };
	menuStarsBackgroundRect = { 512, 0, 256, 224 };
	menuOptionsRect = { 263, 0, 256, 216 };
	menuTitleRect = { 0,0,256, 200 };
	menuBottomRect = { 48, 200, 144, 8 };

	arrowPosition[0] = { 63, 151 };
	arrowPosition[1] = { 63, 167 };
	arrowPosition[2] = { 63, 182 };

	currentArrowPos = &arrowPosition[0];

	cout << "Start Main Title" << endl;

	return true;
}

bool SceneMainTitle::Update()
{

	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN)
	{
		App->audio->PlaySound(SFX::CHANGE_SELECT_SFX, 0);
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
		App->audio->PlaySound(SFX::CHANGE_SELECT_SFX, 0);
		if (currentArrowPos == &arrowPosition[0])
		{
			currentArrowPos = &arrowPosition[2];
		}
		else
		{
			currentArrowPos--;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		
		if (currentArrowPos == &arrowPosition[0])
		{
			App->audio->PlaySound(SFX::SELECT_SFX, 0);
			App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120);
			
		}
	}

	cout << "Update Main Title" << endl;
	return true;
}

bool SceneMainTitle::PostUpdate()
{

	App->render->DrawTexture(texMainMenu, { 0,0 }, &menuBackgroundRect);
	App->render->DrawTexture(texMainMenu, { 0,0 }, &menuStarsBackgroundRect);
	App->render->DrawTexture(texMainMenu, { 0,0 }, &menuTitleRect);
	App->render->DrawTexture(texMainMenu, { 0,8 }, &menuOptionsRect);
	App->render->DrawTexture(texMainMenu, { 56,200 }, &menuBottomRect);
	App->render->DrawTexture(texMenuArrow, *currentArrowPos);

	cout << "PostUpdate Main Title" << endl;
	return true;
}

bool SceneMainTitle::CleanUp(bool finalCleanUp)
{
	if (finalCleanUp)
	{
		delete text;
	}

	Mix_HaltMusic();

	if (currentArrowPos != nullptr)
	{
		currentArrowPos = nullptr;
	}


	cout << "CleanUp Main Title" << endl;
	return true;
}
