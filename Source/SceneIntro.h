#ifndef _SCENEINTRO_H_
#define _SCENEINTRO_H_ 

#include "Scene.h"
#include "Application.h"


class SceneIntro : public Scene
{
public:
	SceneIntro();

	// Destructor
	~SceneIntro();

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



#endif // !_SCENEINTRO_H_



