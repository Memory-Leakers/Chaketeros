#pragma once
#include "Scene.h"

#include "Application.h"
#include "Tile.h"

class SceneLevel2 : public Scene
{
private:

	Tile* level2TileMap;
	SDL_Texture* texMap;

public:

	SceneLevel2();

	// Destructor
	~SceneLevel2();

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

	void CreateYellowFlowers();

	void CreateCoins();

	void InitAssets();
};

