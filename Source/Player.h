#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "Tile.h"
#include "Timer.h"
#include "External/SDL/include/SDL_scancode.h"
#include "External/SDL/include/SDL_render.h"

#define defaultPlayerSpeed 0.15f //Animation only

struct SDL_Texture;

class Particle;

class Obstacle;

class Tile;

enum Dir
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT
};

class Player {

private:

	uint extraCoinsStepSFX, deathSFX, gameOverSFX;

	SDL_Rect bounds;

	bool isFlip = false;

	void dropBomb() {};

	bool canMoveDir[4];

	bool isMoveDie[4];

	bool godMode = false;

	bool posMode = false;

	iPoint mapLimits[3][2] = { {{24, 32}, {216, 192}}, {{24,32}, {472,192}}, {{24, 32}, {216, 192}} };
	
	Tile* tileMap = nullptr;

	Timer playerTimer;

	Obstacle** obstacles = nullptr;

	// Template particle for an end of player
	Particle* playerDestroyed = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;

	// Player texture
	SDL_Texture* texture = nullptr;
	// Bomb texture
	SDL_Texture* texBomb = nullptr;

private:

	void SpecialSound();

public:
	// Position of the player in the map
	iPoint position;

	// Pivot point of the player
	iPoint pivotPoint;

	// Last position of the player in the tile
	iPoint lastTilePos;

	// Position of the player in the tile
	iPoint tilePos;

	// Collider
	Collider* col = nullptr;

	// The speed in which we move the player (pixels per frame)
	int speed = 1; //Movement only

	int pUpFlame = 0;

	int maxBombs = 1;

	bool pendingToDelete = false;

	bool ExtraPoints = false;	

public:
	// Constructor
	Player(Tile* tileMap, Obstacle** obs);

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

	// Callback if will be collision, called when the player intersects with another
	void WillCollision(Collider* col);

	bool InGrid(Collider* col);

	// pos for debug
	iPoint getCurrentTilePos();

	// pos for bomb
	iPoint getCurrentTileWorldPos();
};
#endif // __PLAYER_H__

