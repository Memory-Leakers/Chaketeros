#ifndef _SCENELEVEL1_H_
#define _SCENELEVEL1_H_


#include "Scene.h"

#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "Player.h"
#include "Timer.h"


#include "ModuleEnemy.h"

using namespace std;

struct SDL_Texture;

#define SCENE_OBSTACLES_NUM 256
#define MAX_EMPTY_SPACES 104
#define MAX_POWERUPS 5
#define MAX_STONE 30
#define MAX_ENEMY 4

class SceneLevel1 : public Scene
{
private:
	// Texture
	SDL_Texture* texMap = nullptr;
	SDL_Texture* texFG = nullptr;
	SDL_Texture* texUI = nullptr;
	SDL_Texture* texBomb = nullptr;
	SDL_Texture* texStone = nullptr;
	SDL_Texture* texGlassCapsule = nullptr;
	SDL_Texture* texYellowFlower = nullptr;
	SDL_Texture* texEnemies = nullptr;
	SDL_Texture* texItemDestroyed = nullptr;
	SDL_Texture* texCoin = nullptr;
	SDL_Texture* texPowerUpDestroyed = nullptr;
	SDL_Texture* texCoreMecha = nullptr;
	SDL_Texture* texPowerUps = nullptr;

	// Particle
	// Template particle for an center of explosion
	Particle* explosionCenter = nullptr;

	// Template particle for an middle of explosion
	Particle* explosionMiddle = nullptr;

	// Template particle for an end of explosion
	Particle* explosionEnd = nullptr;

	// Template particle for an end of powerUp
	Particle* powerUpDestroyed = nullptr;

	// Template particle for an end of red flower
	Particle* redFlowerDestroyed = nullptr;

	// Template particle for an end of yellow flower
	Particle* yellowFlowerDestroyed = nullptr;

	// Template particle for an end of mover
	Particle* moverDestroyed = nullptr;

	//	Number of yellow flowers
	int yellowFlowersNum;
	//	Position of render Exceptions
	int renderExceptionPos[3];
	//	Index on the sceneObstacle array of redFlower
	int redFlowerIndex[4];
	//	Index on the sceneObstacle array of the Glass Capsule
	int glassCapsuleIndex;
	//	Number of total seconds
	int totalSeconds;
	//	Number of total minutes
	int minutes;
	// Current second shown on screen
	int currentSecond = 0;
	//Offset for the seconds timer
	int secondsXOffset = 100;
	//Player lifes
	int playerLifes = 3;	//HA DE CAMBIARSE DE SITIO. AL VOLVER DESDE GAME OVER NO SE RESETEA

	uint whistlingSFX, oneMinuteSFX, levelCompleteSFX, extraCoinsBckgSFX;

	//	Counter for Sound Effects
	float BGFX_CoinsCounter = 0;

	//	Boolean to check if both CoreMecha have been destroyed
	bool isLevelCompleted;
	//	Boolean to check if the player has activated the Extra Points event (appear Coins when player completes level and goes to the Glass Capsule)
	bool isExtraPointsActive;
	//	Boolean to check if the time counter has run out of time
	bool isTimeOut;
	//	Boolean to check if there is a change of scene currently
	bool isChangingScene;

	bool debugPowerUp = false;

	//	Timer
	Timer timer;

	//	TileMap
	Tile* tileMap;

public:

	SceneLevel1();

	// Destructor
	~SceneLevel1();

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

	void PrintDebugInformation();

};

#endif