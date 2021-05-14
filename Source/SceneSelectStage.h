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
	};

	SDL_Rect recBigMoney[4]
	{
		{2,85,79,80}, // 0 money
		{166,2,79,80}, // 1 money
		{84,2,79,80}, // 2 money
		{2,2,79,80} // 3 money
	};

	SDL_Rect recInGameUI = { 0, 0, 256, 24 };

	SDL_Rect recBomberman = { 65,2,16,22 };

	Animation stoneCoinAnim;

	iPoint posStoneCoins[3]
	{	
		{ 58, 76 }, // lv3
		{ 101, 81 }, // lv2
		{ 50, 56 }, // lv1
	};

	iPoint posStageSelect[4]
	{
		{ 43, 54 }, // lv1
		{ 94, 78 }, // lv2
		{ 51, 74 }, // lv3
		{ 500, 500 } // exit
	};

	int stageSelectPointer = 0;

	int bigMoneyPointer = 0;

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

