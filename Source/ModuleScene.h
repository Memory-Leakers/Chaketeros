#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Scene.h"

#include "SceneGameOver.h"
#include "SceneIntro.h"
#include "SceneMainTitle.h"
#include "SceneSelectArea.h"
#include "SceneSelectStage.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevelBoss.h"

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"
#include "PlayerSettings.h"

#define SCENES_NUM 8

struct SDL_Texture;

enum SCENE_NUM
{
	SCENE_INTRO,
	SCENE_MAINMENU,
	SCENE_AREA,
	SCENE_STAGE,
	SCENE_LEVEL1,
	SCENE_LEVEL2,
	SCENE_LEVELBOSS,
	SCENE_GAMEOVER
};

class ModuleScene : public Module
{
public:
	// Constructor
	ModuleScene();

	// Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void WillCollision(Collider* c1, Collider* c2) override;

	bool ChangeCurrentScene(uint index, int frames);

	bool CleanUp() override;

	Scene* currentScene = nullptr;

	Scene* scenes[SCENES_NUM] = { nullptr };

	PlayerSettings* playerSettings = nullptr;

	bool isLevelCompleted[3];	//TODO: Cambiar el uso de esta variable en las escenas Level1 y Level2!!!

	int currentLevel = 0;

	int lastSceneID;

private:

	enum FadeSteps
	{
		FADE_NONE,
		FADE_OUT,
		FADE_IN
	};

	SDL_Rect screenRect;

	FadeSteps currentStep = FADE_NONE;

	int currentFrame = 0, maxFrames = 0;

	int newScene;

	SDL_Scancode debugKeys[8] = { SDL_SCANCODE_1, SDL_SCANCODE_2 , SDL_SCANCODE_3 , SDL_SCANCODE_4 ,
								SDL_SCANCODE_5 , SDL_SCANCODE_6 , SDL_SCANCODE_7 ,SDL_SCANCODE_8 };


	void DebugChangeScene();	
};

#endif // __MODULESCENE_H__
