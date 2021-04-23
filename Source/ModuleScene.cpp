#include "ModuleScene.h"


ModuleScene::ModuleScene()
{
	scenes[0] = new SceneIntro();
	scenes[1] = new SceneMainTitle();
	scenes[2] = new SceneSelectArea();
	scenes[3] = new SceneSelectStage();
	scenes[4] = new SceneLevel1();
	scenes[5] = new SceneGameOver();
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Start()
{
	bool ret = true;


	screenRect = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };	//Screen-size rectangle
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	currentScene = scenes[LEVEL1_SCENE];
	currentScene->Start();

	return ret;
}

UpdateResult ModuleScene::PreUpdate()
{
	currentScene->PreUpdate();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::Update()
{


	if (currentStep == FADE_NONE) { currentScene->Update(); return UpdateResult::UPDATE_CONTINUE; }	//Si no hay FADE solo se ejecuta el UPDATE de la CURRENT SCENE

	if (currentStep == FADE_IN)		//Si hay FADE IN, se ejecuta el Update HASTA QUE EL RECTANGULO NEGRO tenga opacidad m�xima
	{
		currentFrame++;
		currentScene->Update();
		if (currentFrame >= maxFrames)	//Si el rect�ngulo negro tiene opacidad m�xima, cambiamos de escena e incializamos la siguiente
		{
			currentScene->CleanUp(false);
			currentScene = scenes[newScene];
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

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleScene::PostUpdate()
{

	currentScene->PostUpdate();

	if (currentStep != FADE_NONE)
	{
		float fadeRatio = (float)currentFrame / (float)maxFrames;

		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &screenRect);
	}


	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	currentScene->OnCollision(c1, c2);
}

void ModuleScene::ChangeCurrentScene(uint index, int frames)	//CleanUp current scene, change current scene (index), Start current Scene
{
	currentStep = FADE_IN;
	maxFrames = frames;
	currentFrame = 0;
	newScene = index;

	/*currentScene->CleanUp();
	currentScene = scenes[index];
	currentScene->Start();
	*/
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
	return true;
}
