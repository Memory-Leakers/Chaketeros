#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "Tile.h"

#include "External/SDL/include/SDL_scancode.h"
#include "External/SDL/include/SDL_render.h"

//class ModuleEntity;

#define defaultPlayerSpeed 0.1f //Animation only
struct SDL_Texture;

enum Dir
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

class Player {

private:
	int lives = 2;
	int score = 0;

	int pUpKick = 0;
	int pUpVest = 0;

	SDL_Rect bounds;

	bool isFlip = false;

	void dropBomb() {};

	bool canMoveDir[4];

protected:

public:
	// Constructor
	Player();

	// Destructor
	~Player();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start();

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update();

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate();

	// Collision callback, called when the player intersects with another
	void OnCollision(Collider* col);

	void WillCollision(Collider* col);

	iPoint getCurrentTilePos();

	// Position of the player in the map
	iPoint position;

	//
	Collider* col = nullptr;

	// The speed in which we move the player (pixels per frame)
	int speed = 1; //Movement only

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;

	int pUpFlame = 0;

	int maxBombs = 1;

	iPoint pivotPoint;

	bool pendingToDelete = false;
};
#endif // __PLAYER_H__

