
#ifndef _SCENEPASSWORD_H_
#define _SCENEPASSWORD_H_

#include "Scene.h"
#include "Tile.h"
#include "NumText.h"
#include "Application.h"
#include "FadeInOut.h"

using namespace std;

struct SDL_Texture;

struct SDL_Rect;

class Particle;

class Timer;

class ScenePassword:public Scene
{
private:

	int nums[4] = { 0,0,0,0 }, cont = 0;

	int* currentNumPos;

	bool isPasswordCorrect = false;

	SDL_Texture* texScenePassword;

	SDL_Rect PasswordRect, ArrowsRect,BackgroundRect,KangarooRect;

	Animation BombermanAndSpaceship;

	// Arrow Position and current Arrow
	iPoint arrowNumPosition[4],NumPos[4];

	iPoint* currentArrowPos = nullptr;

	uint changeSelectSFX, selectSFX;

	Particle* starParticle;

	Timer particleTime;

public:

	ScenePassword();

	~ScenePassword();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	bool CleanUp(bool finalCleanUp = true) override;

	void Comprovation();

};

#endif