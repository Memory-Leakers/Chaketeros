#ifndef _SCENE_H_
#define _SCENE_H_

#include "Collider.h"

class Scene
{
public:
	// Constructor
	Scene();

	// Destructor
	~Scene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	virtual bool Start();

	// Called at the middle of the application loop
	// Updates the scene's background animations
	virtual bool Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	virtual bool PostUpdate();

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual bool CleanUp();


};


#endif //_SCENE_H_
