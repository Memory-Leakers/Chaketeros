#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"

#include "External/SDL/include/SDL_scancode.h"
#include "External/SDL/include/SDL_render.h"

//class ModuleEntity;

#define defaultPlayerSpeed 0.1f //Animation only
struct SDL_Texture;

class Player {

private:
	int lives = 2;
	int score = 0;
	int maxBombs = 1;
	bool pUpBomb = false;
	bool pUpFlame = false;
	bool pUpKick = false;
	bool pUpVest = false;

	SDL_Rect bounds;

	bool isFlip = false;

	void dropBomb() {

	};
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

	//Test Sound
};
#endif // __PLAYER_H__

