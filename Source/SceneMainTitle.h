#ifndef _SCENEMAINTITLE_H_
#define _SCENEMAINTITLE_H_

#include "Scene.h"



class SceneMainTitle : public Scene
{
public:
	SceneMainTitle();

	// Destructor
	~SceneMainTitle();

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

	SDL_Texture* texMainMenu;
	SDL_Texture* texMenuArrow;
	SDL_Rect menuBackgroundRect;
	SDL_Rect menuStarsBackgroundRect;
	SDL_Rect menuOptionsRect;
	SDL_Rect menuBottomRect;
	SDL_Rect menuTitleRect;
	iPoint arrowPosition[3];
	iPoint* currentArrowPos;
};

#endif