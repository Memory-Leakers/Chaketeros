#ifndef _SCENESELECTAREA_H_
#define _SCENESELECTAREA_H_

#include "Scene.h"



class SceneSelectArea : public Scene
{
public:
	SceneSelectArea();

	// Destructor
	~SceneSelectArea();

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


#endif // !_SCENESELECTAREA_H_


