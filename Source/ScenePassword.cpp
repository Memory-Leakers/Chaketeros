#include "ScenePassword.h"
#include "Application.h"
#include "Timer.h"
#include "Particle.h"

#include <iostream>
using namespace std;

#pragma region Variables
NumText PasswordNums;
#pragma endregion

ScenePassword::ScenePassword() {

	ID = 8;

	BombermanAndSpaceship.PushBack({ 56,291,66,81 });
	BombermanAndSpaceship.PushBack({ 137,291,66,81 });
	BombermanAndSpaceship.speed = 0.03f;
	BombermanAndSpaceship.hasIdle = false;
	BombermanAndSpaceship.loop = true;


};

ScenePassword::~ScenePassword() {


};

bool ScenePassword::Start() {

	Mix_VolumeMusic(15);
	App->audio->PlayMusic("Assets/Audio/Music/PasswordScreen.ogg", 1.5f);

	texScenePassword = App->textures->Load("Assets/Images/Sprites/UI_Sprites/PasswordMenu.png");
	BackgroundRect = { 0,0,256,224 };
	ArrowsRect = {216,235,16,43};
	PasswordRect = { 269,233,175,27 };
	KangarooRect = { 327,286, 48,61 };

#pragma region Arrow Positions Setup
	arrowNumPosition[0] = { 60, 72 };
	arrowNumPosition[1] = { 100, 72 };
	arrowNumPosition[2] = { 140, 72 };
	arrowNumPosition[3] = { 180, 72 };
	
	currentArrowPos = &arrowNumPosition[0];
#pragma endregion

	NumPos[0] = { 61,86 };
	NumPos[1] = { 100,86 };
	NumPos[2] = { 140,86 };
	NumPos[3] = { 179,86 };

	PasswordNums.Start();

	currentNumPos = &nums[0];

	changeSelectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_ChangeOptionSound.wav");
	selectSFX = App->audio->LoadSound("Assets/Audio/SFX/General_Sounds/MM_SelectSound.wav");

	BombermanAndSpaceship.Reset();

	starParticle = new Particle(200.0f, 0.2f, texScenePassword);

	starParticle->anim.PushBack({ 245, 283, 4, 5 });
	starParticle->anim.PushBack({ 253, 291, 4, 5 });
	starParticle->anim.loop = true;

	return true;
}

bool ScenePassword::Update() {
	GamePad& pad = App->input->pads[0];

	BombermanAndSpaceship.Update();

	particleTime.Update();

	if (particleTime.getDeltaTime() > 0.15f)
	{
		particleTime.Reset();
		int sig[2] = { 1,-1 };

		for (int i = 0; i < 2; i++)
		{
			starParticle->setSpeed({ (rand() % 3 + 1) * sig[rand() % 2], (rand() % 3 + 1) * sig[rand() % 2] });
			App->particle->AddParticle(*starParticle, 128, 120, Type::NONE);
		}
	}
#pragma region Input Arrow Position Logic

	//Check Input to change Arrow Position
	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_DOWN || App->input->keys[SDL_SCANCODE_D] == KEY_DOWN || pad.right == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		if (currentArrowPos == &arrowNumPosition[3] && currentNumPos == &nums[3])
		{
			currentArrowPos = &arrowNumPosition[0];
			currentNumPos = &nums[0];
		}
		else
		{
			currentArrowPos++;
			currentNumPos++;
		}
	}
	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_DOWN || App->input->keys[SDL_SCANCODE_A] == KEY_DOWN || pad.left == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		if (currentArrowPos == &arrowNumPosition[0] && currentNumPos == &nums[0])
		{
			currentArrowPos = &arrowNumPosition[3];
			currentNumPos = &nums[3];
		}
		else
		{
			currentArrowPos--;
			currentNumPos--;
		}
	}
	
	if (App->input->keys[SDL_SCANCODE_UP] == KEY_DOWN || App->input->keys[SDL_SCANCODE_W] == KEY_DOWN || pad.up == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		for (int i = 0; i < 4; i++) {
			if (currentNumPos == &nums[i])
			{
				if (nums[i] == 9) {
					nums[i] = 0;
				}
				else {
					nums[i]++;
				}
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_DOWN || App->input->keys[SDL_SCANCODE_S] == KEY_DOWN || pad.down == KEY_DOWN)
	{
		App->audio->PlaySound(changeSelectSFX, 0);
		for (int i = 0; i < 4; i++) {
			if (currentNumPos == &nums[i])
			{
				/*if (nums[i] == 0) {
					cont = 0;
				}*/
				if (nums[i] == 0 /*&& cont == 0*/) {
					nums[i] = 9;

					/*cont++;*/
				}
				else  {
					/*if (cont != 0)*/
					nums[i]--;
				}
			}
		}
	}
#pragma endregion
#pragma region Select Option Logic

	//Select an option based on the arrow position
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_DOWN || pad.a == KEY_DOWN)
	{
		cout << "kek" << endl;
		Comprovation();
		if (isPasswordCorrect) {

			App->audio->PlaySound(selectSFX, 0);
			App->scene->ChangeCurrentScene(SCENE_LEVEL2, 80);
		}
		
	}

#pragma endregion

	return true;
}

bool ScenePassword::PostUpdate()
{

	App->render->AddTextureRenderQueue(texScenePassword, { 0,0 }, &BackgroundRect, 0, 0);
	App->render->AddTextureRenderQueue(texScenePassword, { 43,31 }, &PasswordRect, 2, 0);
	App->render->AddTextureRenderQueue(texScenePassword, { 167,135 }, &KangarooRect, 2, 0);
	App->render->AddTextureRenderQueue(texScenePassword, { 48, 121 }, &BombermanAndSpaceship.GetCurrentFrame(), 2, 1);
	App->render->AddTextureRenderQueue(texScenePassword, *currentArrowPos, &ArrowsRect, 2, 0);
	PasswordNums.DrawNum(nums[0], NumPos[0], 3.0f, 2,0,1);
	PasswordNums.DrawNum(nums[1], NumPos[1], 3.0f, 2,0,1);
	PasswordNums.DrawNum(nums[2], NumPos[2], 3.0f, 2,0,1);
	PasswordNums.DrawNum(nums[3], NumPos[3], 3.0f, 2,0,1);
	
	
	

	return true;
}

bool ScenePassword::CleanUp(bool finalCleanUp)
{

	cout << "CleanUp Password Scene" << endl;
	if (!finalCleanUp)
	{
		App->textures->CleanUpScene();
		App->audio->CleanUpScene();
		App->particle->CleanUpScene();

	}

	if (starParticle != nullptr)
	{
		delete starParticle;
		starParticle = nullptr;
	}

	return true;
}

void ScenePassword::Comprovation() {

	int password[4] = { 6,8,0,0 };
	for (int i = 0; i < 4; i++) {
		if (nums[i] == password[i]) {
			isPasswordCorrect = true;
		}
		else {
			isPasswordCorrect = false;
			break;
		}
	}
}