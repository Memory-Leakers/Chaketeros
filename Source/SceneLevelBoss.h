#ifndef _SCENELEVEL2_H_
#define _SCENELEVEL2_H_

#include "Scene.h"


class SceneLevelBoss : public Scene
{
public:
	SceneLevelBoss();

	// Destructor
	~SceneLevelBoss();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	bool PreUpdate() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	bool Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	bool PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void WillCollision(Collider* c1, Collider* c2) override;

	bool CleanUp(bool finalCleanUp = true) override;

	void CreateScene();

	void InitAssets();

};
#endif

