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

// Load assets
bool ModuleScene::Start()
{
	bool ret = true;

	currentScene = scenes[4];
	currentScene->Start();

	return ret;
}

UpdateResult ModuleScene::Update()
{
	currentScene->Update();

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	currentScene->PostUpdate();
	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	currentScene->OnCollision(c1, c2);
}

void ModuleScene::ChangeCurrentScene(uint index)	//CleanUp current scene, change current scene (index), Start current Scene
{
	currentScene->CleanUp();
	currentScene = scenes[index];
	currentScene->Start();
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