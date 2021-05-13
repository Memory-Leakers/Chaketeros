#ifndef _SCENESELECTSTAGE_H_
#define _SCENESELECTSTAGE_H_

#include "Scene.h"
#include "Application.h"
#include "Animation.h"
#include "SDL_image/include/SDL_image.h"

class SceneSelectStage : public Scene
{
private:
	SDL_Texture* texMap = nullptr;
	SDL_Texture* texUISelect = nullptr;
	SDL_Texture* texStages = nullptr;
	SDL_Texture* texStoneCoin = nullptr;
	SDL_Texture* texInGameUI = nullptr;
	SDL_Texture* texBigStoneCoins = nullptr;
	SDL_Texture* texBomberman = nullptr;

	SDL_Rect recStages[4]
	{
		{0, 0, 77,   63}, //Stage1
		{0, 64, 77,  63}, //Stage2
		{0, 128, 77, 63}, //Sage3
		{0, 192, 77, 63}  //Exit
	};

	SDL_Rect recStageSelect[2]
	{
		{118, 3, 112, 81}, //SelectMap
		{3, 88, 30,   20}, //SelectUI

		//Respect pos
		//select1(arriba iz) : 130,34
		//select2(abajo dr) : 181,58
		//select3(abajo iz) : 138,54
	};

	SDL_Rect recInGameUI = { 0, 0, 256, 24 };

	SDL_Rect recBomberman = { 65,2,16,22 };

	Animation stoneCoinAnim;

	iPoint stoneCoinsPos[3];

	iPoint stageSelectPos[4];

	int stageSelectPointer = 0;

public:
	SceneSelectStage();

	// Destructor
	~SceneSelectStage();

	void ModifyStagePointer(int mod);

	void InitAssets();

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
};

#endif

