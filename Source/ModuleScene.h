#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Scene.h"

#include "SceneGameOver.h"
#include "SceneIntro.h"
#include "SceneMainTitle.h"
#include "SceneSelectArea.h"
#include "SceneSelectStage.h"
#include "SceneLevel1.h"

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"


#define SCENES_NUM 6

struct SDL_Texture;

enum SCENE_NUM
{
	INTRO_SCENE,
	MAIN_MENU_SCENE,
	AREA_SCENE,
	STAGE_SCENE,
	LEVEL1_SCENE,
	GAME_OVER_SCENE
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

	void ChangeCurrentScene(uint index, int frames, int sceneScore = 0);

	bool CleanUp() override;

	//Text* text = nullptr;

	Scene* currentScene = nullptr;

	Scene* scenes[SCENES_NUM] = { nullptr };

	int currentScore;

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
};

#endif // __MODULESCENE_H__
