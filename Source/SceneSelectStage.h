#ifndef _SCENESELECTSTAGE_H_
#define _SCENESELECTSTAGE_H_

#include "Scene.h"

class SceneSelectStage : public Scene
{
public:
	SceneSelectStage();

	// Destructor
	~SceneSelectStage();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	bool CleanUp() override;

};

#endif

