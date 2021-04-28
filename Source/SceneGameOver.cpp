#include "SceneGameOver.h"

#include <iostream>
using namespace std;



SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

bool SceneGameOver::Start()
{
	cout << "Start Game Over" << endl;

	cout << "Score: " << this->score << endl;

	Mix_HaltMusic();

	App->audio->PlayMusic("Assets/Audio/Music/GameOverMusic.ogg", 1.5f);

	texGameOver = App->textures->Load("Assets/Images/Sprites/UI_Sprites/GameOver.png");
	texGameOverMisc = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");

	gameOverBackgroundRec = {256, 0, 256, 224};

	gameOverPointerRec = { 0,48,15,15 };

	gameOverAnim.PushBack({ 0,0,256,224 });
	gameOverAnim.PushBack({ 0,224,256,224 });
	gameOverAnim.speed = 0.05f;
	gameOverAnim.hasIdle = false;

	pointerPos[0] = { 63,78 };
	pointerPos[1] = { 63,110 };

	currentPointerPos = &pointerPos[0];
	return true;
}

bool SceneGameOver::Update()
{
	//cout << "Update Game Over" << endl;
	gameOverAnim.Update();


	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN)
	{
		App->audio->PlaySound(SFX::CHANGE_SELECT_SFX, 0);
		if (currentPointerPos == &pointerPos[1])
		{
			currentPointerPos = &pointerPos[0];
		}
		else
		{
			currentPointerPos++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN || App->input->keys[SDL_SCANCODE_W] == KEY_DOWN)
	{
		App->audio->PlaySound(SFX::CHANGE_SELECT_SFX, 0);
		if (currentPointerPos == &pointerPos[0])
		{
			currentPointerPos = &pointerPos[1];
		}
		else
		{
			currentPointerPos--;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->audio->PlaySound(SFX::SELECT_SFX, 0);
		if (currentPointerPos == &pointerPos[0])
		{
			App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120);
		}
		else if (currentPointerPos == &pointerPos[1])
		{
			App->scene->ChangeCurrentScene(INTRO_SCENE, 120);
		}
	}
	return true;
}

bool SceneGameOver::PostUpdate()
{
	App->render->DrawTexture(texGameOver, { 0,0 }, &gameOverBackgroundRec);
	App->render->DrawTexture(texGameOver, { 0,0 }, &gameOverAnim.GetCurrentFrame());
	App->render->DrawTexture(texGameOverMisc, *currentPointerPos, &gameOverPointerRec);

	//cout << "PostUpdate Game Over" << endl;
	return true;
}

bool SceneGameOver::CleanUp(bool finalCleanUp)
{
	if (finalCleanUp)
	{
		delete text;
	}
	/*cout << "CleanUp Game Over" << endl;*/
	return true;
}