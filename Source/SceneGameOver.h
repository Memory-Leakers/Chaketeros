#ifndef _SCENEGAMEOVER_H_
#define _SCENEGAMEOVER_H

#include "Scene.h"
//#include "Application.h";

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

};


#endif // !_SCENEGAMEOVER_H_



