#include "SceneGameOver.h"

using namespace std;

vector <int> digitVec;

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

	#pragma region Pointer Setup
	pointerPos[0] = { 63,78 };
	pointerPos[1] = { 63,110 };

	currentPointerPos = &pointerPos[0];
	#pragma endregion

	//Reset variables
	pressedContinue = false;
	//Convert current score to Textures
	DrawGameOverScore();
	
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
	#pragma endregion

	#pragma region Select Option Logic
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->audio->PlaySound(SFX::SELECT_SFX, 0);

		if (currentPointerPos == &pointerPos[0])
		{
			pressedContinue = true;
			App->scene->ChangeCurrentScene(LEVEL1_SCENE, 120);
		}
		else if (currentPointerPos == &pointerPos[1])
		{
			App->scene->ChangeCurrentScene(INTRO_SCENE, 120);
		}

	}
	#pragma endregion

	return true;
}

bool SceneGameOver::PostUpdate()
{
	#pragma region Drawing Textures 
	App->render->DrawTexture(texGameOver, { 0,0 }, &gameOverBackgroundRec);
	
	if (pressedContinue) { App->render->DrawTexture(texGameOverContinue, { 0,0 }, &gameOverContinueAnim.GetCurrentFrame()); }

	else { App->render->DrawTexture(texGameOver, { 0,0 }, &gameOverAnim.GetCurrentFrame()); }
	
	App->render->DrawTexture(texGameOverMisc, *currentPointerPos, &gameOverPointerRec);
	#pragma endregion

	#pragma region Display Game Over Score Logic
	bool isOneBefore = false;
	int xOffset = 15;
	int xPos = 130;

	for (int i = 0; i < totalDigits; i++)
	{
		if (isOneBefore)
		{
			if (!digitVec.at(i) == 1)
			{
				xOffset = 12;				
			}
			else 
			{
				xOffset = 11;
			}
			isOneBefore = false;
		}	

		if (digitVec.at(i) == 1)
		{
			if (xOffset == 15) 
			{
				 xOffset = 12;
			}
			isOneBefore = true;
		}
				
		App->render->DrawTexture(texGameOverMisc, { xPos +(xOffset * i), 152 }, &numRec[digitVec.at(i)]);
	}
	#pragma endregion

	return true;
}

void SceneGameOver::DrawGameOverScore()
{	
	for (int i = 0; i < 10; i++)
	{
		numRec[i] = { 14 * i, 64, 14, 15 };
	}

	stack<int> digits;

	int currentScore = score;

	while (currentScore > 0)
	{
		int digit = currentScore % 10;
		currentScore /= 10;
		digits.push(digit);
	}

	totalDigits = digits.size();

	while (!digits.empty())
	{
		int digit = digits.top();
		digitVec.push_back(digit);
		digits.pop();
		cout << digit << endl;
	}	
}

bool SceneGameOver::CleanUp(bool finalCleanUp)
{
	if (finalCleanUp)
	{
		delete text;
	}

	digitVec.clear();
	digitVec.shrink_to_fit();

	return true;
}
