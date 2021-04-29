#ifndef _SCENEGAMEOVER_H_
#define _SCENEGAMEOVER_H_

#include "Scene.h"
#include "Application.h"
#include "Animation.h"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class SceneGameOver : public Scene
{
public:
	SceneGameOver();

	// Destructor
	~SceneGameOver();

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

	void DrawGameOverScore();

	SDL_Texture* texGameOver = nullptr;
	SDL_Texture* texGameOverMisc = nullptr;
	SDL_Texture* texGameOverContinue = nullptr;

	SDL_Rect gameOverBackgroundRec;
	SDL_Rect gameOverPointerRec;
	SDL_Rect numRec[10];


	Animation gameOverAnim, gameOverContinueAnim;

	iPoint pointerPos[2];
	iPoint* currentPointerPos;

	int totalDigits;
	vector <int> digitVec;

	bool pressedContinue;
	
};

#endif // !_SCENEGAMEOVER_H_



