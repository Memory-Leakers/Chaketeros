#include "ModuleScene.h"
#include "DrawPoints.h"
#include <time.h>


PlayerSettings* playerSettings = nullptr;

DrawPoints drawPoints;

ModuleScene::ModuleScene()
{
	scenes[0] = new SceneIntro();
	scenes[1] = new SceneMainTitle();
	scenes[2] = new SceneSelectArea();
	scenes[3] = new SceneSelectStage();
	scenes[4] = new SceneLevel1();
	scenes[5] = new SceneLevel2();
	scenes[6] = new SceneLevelBoss();
	scenes[7] = new SceneGameOver();
	scenes[8] = new ScenePassword();

	srand(time(NULL));
	playerSettings = PlayerSettings::Instance();
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;

	screenRect = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };	//Screen-size rectangle
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	currentScene = scenes[SCENE_INTRO];

	drawPoints.Start();


	if(currentScene == nullptr)
	{
		return ret;
	}

	currentScene->Start();

	return ret;
}

UpdateResult ModuleScene::PreUpdate()
{
	if (currentScene == nullptr || App->isPaused)
	{
		return UpdateResult::UPDATE_CONTINUE;
	}

	currentScene->PreUpdate();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::Update()
{
	drawPoints.Update();

	if (App->input->keys[SDL_SCANCODE_BACKSPACE] == KEY_DOWN)
	{
		App->scene->ChangeCurrentScene(currentScene->lastID, 60);
	}

	#pragma region Update and FadeInOut

	if (currentScene == nullptr || App->isPaused)
	{
		return UpdateResult::UPDATE_CONTINUE;
	}
		
	if (currentStep == FADE_NONE) //Si no hay FADE solo se ejecuta el UPDATE de la CURRENT SCENE
	{ 
		currentScene->Update();
		DebugChangeScene(); 

		return UpdateResult::UPDATE_CONTINUE; 
	}	

	if (currentStep == FADE_IN)		//Si hay FADE IN, se ejecuta el Update HASTA QUE EL RECTANGULO NEGRO tenga opacidad m�xima
	{
		currentFrame++;
		currentScene->Update();
		if (currentFrame >= maxFrames)	//Si el rect�ngulo negro tiene opacidad m�xima, cambiamos de escena e incializamos la siguiente
		{
			lastSceneID = currentScene->getID();

			currentScene->CleanUp(false);
			currentScene = scenes[newScene];

			drawPoints.Reset();
			drawPoints.Start();

			App->render->ResetCamera();
			currentScene->lastID = lastSceneID;

			currentScene->Start();
			currentStep = FADE_OUT;
			return UpdateResult::UPDATE_CONTINUE;
		}
		return UpdateResult::UPDATE_CONTINUE;
	}
	else //Si no es FADE_NONE o FADE_IN deber?ser FADE_OUT
	{
		--currentFrame;		//Restamos la opacidad del rect�ngulo negro
		currentScene->Update();
		if (currentFrame <= 0) { currentStep = FADE_NONE; }	//Si la opacidad es 0, volvemos a FADE_NONE
	}
	#pragma endregion


	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::PostUpdate()
{
	if (currentScene == nullptr)
	{
		return UpdateResult::UPDATE_CONTINUE;
	}
	
	currentScene->PostUpdate();

	if (currentStep != FADE_NONE)
	{
		float fadeRatio = (float)currentFrame / (float)maxFrames;

		App->render->AddRectRenderQueue(screenRect, { 0,0,0,(Uint8)(fadeRatio * 255.0f) });
	}
	
	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	currentScene->OnCollision(c1, c2);
}

void ModuleScene::WillCollision(Collider* c1, Collider* c2)
{
	currentScene->WillCollision(c1, c2);
}

//CleanUp current scene, change current scene (index), Start current Scene
bool ModuleScene::ChangeCurrentScene(uint index, int frames)	
{
	if (currentStep != FADE_NONE) return false;
	
	currentStep = FADE_IN;
	maxFrames = frames;
	currentFrame = 0;
	newScene = index;
	return true;
}

void ModuleScene::DrawPoints(int score, iPoint position)
{
	drawPoints.DrawScore(score, position);
}

bool ModuleScene::CleanUp()
{
	for (int i = 0; i < SCENES_NUM; i++)
	{
		if (scenes[i] != nullptr)
		{
			scenes[i]->CleanUp();	//CleanUp all scenes (in case the Application is shut down)
			delete scenes[i];
			scenes[i] = nullptr;
		}
	}

	playerSettings->Release();

	return true;
}

void ModuleScene::DebugChangeScene()
{
	if (App->input->keys[SDL_SCANCODE_LCTRL] == KEY_REPEAT)
	{
		for (int i = 0; i < SCENES_NUM; i++)
		{
			if (App->input->keys[debugKeys[i]] == KEY_DOWN)
			{
				ChangeCurrentScene(i, 90);
			}
		}

		if (App->input->keys[SDL_SCANCODE_R] == KEY_DOWN)
		{
			ChangeCurrentScene(currentScene->getID(), 90);
		}
	}
}
