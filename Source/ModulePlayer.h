#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"

#include "External/SDL/include/SDL_scancode.h"

//class ModuleEntity;

struct SDL_Texture;

class ModulePlayer : public Module{

	private:
		
	protected:
		

	public:
		// Constructor
		ModulePlayer();

		// Destructor
		~ModulePlayer();

		// Called when the module is activated
		// Loads the necessary textures for the player
		bool Start() ;

		// Called at the middle of the application loop
		// Processes new input and handles player movement
		UpdateResult Update() ;

		// Called at the end of the application loop
		// Performs the render call of the player sprite
		UpdateResult PostUpdate() ;

		// Collision callback, called when the player intersects with another collider
		void OnCollision(Collider* c1, Collider* c2) ;

		// Position of the player in the map
		iPoint position;

		//Collider
		Collider* col = nullptr;

		// The speed in which we move the player (pixels per frame)
		int speed = 1;

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

#endif // __MODULEPLAYER_H__