#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "ModuleEntity.h"

#include "External/SDL/include/SDL_scancode.h"

class ModulePlayer : public ModuleEntity {

	private:

	protected:
		// Constructor
		ModulePlayer();

		// Destructor
		~ModulePlayer();

		// Called when the module is activated
		// Loads the necessary textures for the player
		bool Start() override;

		// Called at the middle of the application loop
		// Processes new input and handles player movement
		UpdateResult Update() override;

		// Called at the end of the application loop
		// Performs the render call of the player sprite
		UpdateResult PostUpdate() override;

		// Collision callback, called when the player intersects with another collider
		void OnCollision(Collider* c1, Collider* c2) override;

		// Position of the player in the map
		iPoint position;

		//Collider
		c.type = PLAYER;

		// The speed in which we move the player (pixels per frame)
		int speed = 1;

		// The player spritesheet loaded into an SDL_Texture
		SDL_Texture* texture = nullptr;
	
		// The pointer to the current player animation
		// It will be switched depending on the player's movement direction
		Animation* currentAnimation = nullptr;

		// A set of animations
		Animation idleAnim;
		Animation forwardAnim;
		Animation backwardAnim;

		//Test Sound 

	public:
};

#endif // __MODULEPLAYER_H__