#include "SceneGameOver.h"

using namespace std;

NumText gameOverScore;

SDL_Rect debugRect;

SceneGameOver::SceneGameOver()
{
	#pragma region Init Anim
	gameOverAnim.PushBack({ 0,0,256,224 });
	gameOverAnim.PushBack({ 0,224,256,224 });
	gameOverAnim.speed = 0.05f;
	gameOverAnim.hasIdle = false;

	gameOverContinueAnim.PushBack({ 0,0, 256, 224 });
	gameOverContinueAnim.PushBack({ 512,0, 256, 224 });
	gameOverContinueAnim.PushBack({ 768,0, 256, 224 });
	gameOverContinueAnim.PushBack({ 1024,0, 256, 224 });
	gameOverContinueAnim.PushBack({ 1280,0, 256, 224 });
	gameOverContinueAnim.PushBack({ 1536,0, 256, 224 });
	gameOverContinueAnim.speed = 0.05f;
	gameOverContinueAnim.hasIdle = false;
	gameOverContinueAnim.loop = false;
	#pragma endregion
}

SceneGameOver::~SceneGameOver()
{
}

bool SceneGameOver::Start()
{
	cout << "Start Game Over" << endl;

	cout << "Score: " << this->score << endl;

	#pragma region Music Setup
	Mix_HaltMusic();

	App->audio->PlayMusic("Assets/Audio/Music/GameOverMusic.ogg", 1.5f);
	#pragma endregion

	#pragma region Textures and Animations Setup
	texGameOver = App->textures->Load("Assets/Images/Sprites/UI_Sprites/GameOver.png");
	texGameOverMisc = App->textures->Load("Assets/Images/Sprites/UI_Sprites/Misc.png");
	texGameOverContinue = App->textures->Load("Assets/Images/Sprites/UI_Sprites/GameOverContinue.png");

	gameOverBackgroundRec = {256, 0, 256, 224};

	gameOverPointerRec = { 0,48,15,15 };
	#pragma endregion

	#pragma region Pointer Setup
	pointerPos[0] = { 63,78 };
	pointerPos[1] = { 63,110 };

	currentPointerPos = &pointerPos[0];
	#pragma endregion

	// Reset anim
	gameOverAnim.Reset();
	gameOverContinueAnim.Reset();

	//Reset variables
	pressedContinue = false;
	
	gameOverScore.Start();

	changeSelectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_ChangeOptionSound.wav");
	selectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_SelectSound.wav");
	
	return true;
}

bool SceneGameOver::Update()
{
	//Animation Logic
	gameOverAnim.Update();
	if (pressedContinue) { gameOverContinueAnim.Update(); }

	#pragma region Input Pointer Position Logic
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
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
		App->audio->PlaySound(changeSelectSFX, 0);
		if (currentPointerPos == &pointerPos[0])
		{
			currentPointerPos = &pointerPos[1];
		}
		else
		{
			currentPointerPos--;
		}
	}
	#pragma endregion

	#pragma region Select Option Logic
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->audio->PlaySound(selectSFX, 0);

		App->scene->playerSettings->Reset();

		if (currentPointerPos == &pointerPos[0] && !pressedContinue)
		{		
			if(App->scene->ChangeCurrentScene(SCENE_LEVEL1, 90))
			{
				pressedContinue = true;
			}
		}
		else if (currentPointerPos == &pointerPos[1])
		{
			App->scene->ChangeCurrentScene(SCENE_INTRO, 90);
		}
	}
	#pragma endregion

	return true;
}

bool SceneGameOver::PostUpdate()
{
	#pragma region Drawing Textures 
	
	App->render->AddTextureRenderQueue(texGameOver, { 0,0 }, &gameOverBackgroundRec, 2);
	
	if (pressedContinue) 
	{
		debugRect = gameOverContinueAnim.GetCurrentFrame();
		App->render->AddTextureRenderQueue(texGameOverContinue, { 0,0 }, &debugRect,2);
	}
	else 
	{
		App->render->AddTextureRenderQueue(texGameOver, { 0,0 }, &gameOverAnim.GetCurrentFrame(), 2);
	}

	App->render->AddTextureRenderQueue(texGameOverMisc, *currentPointerPos, &gameOverPointerRec, 2);
	#pragma endregion

	#pragma region Display Game Over Score Logic
	gameOverScore.DrawNum(score, { 130, 152 }, 1);
	#pragma endregion

	return true;
}

bool SceneGameOver::CleanUp(bool finalCleanUp)
{
	if (!finalCleanUp)
	{
		App->textures->CleanUpScene();
		App->audio->CleanUpScene();
	}

	return true;
}
