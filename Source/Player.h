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

class Particle;

#define defaultPlayerSpeed 0.15f //Animation only
struct SDL_Texture;

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
	int lives = 2;
	int score = 0;

	int pUpKick = 0;
	int pUpVest = 0;

	SDL_Rect bounds;

	bool isFlip = false;

	void dropBomb() {};

	bool canMoveDir[4];

	bool isMoveDie[4];

	bool godMode = false;

	bool posMode = false;
	

	Tile* level1Tile = nullptr;

	Timer playerTimer;

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

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

protected:

public:
	// Constructor
	Player(Tile* level1Tile);

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

	// pos for debug
	iPoint getCurrentTilePos();

	// pos for bomb
	iPoint getCurrentTilewWorldPos();

	// Position of the player in the map
	iPoint position;

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

	iPoint pivotPoint;

	bool pendingToDelete = false;

	bool ExtraPoints = false;


	//GETTERS AND SETTERS
	int getScore() {
		return score;
	}

	int getLives() {
		return lives;
	}
};
#endif // __PLAYER_H__

