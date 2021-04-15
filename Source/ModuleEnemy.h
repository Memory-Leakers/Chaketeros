#pragma once

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"


#define defaultSpeed 0.1f

struct SDL_Texture;

class ModuleEnemy : public Module{

	private:

	protected:
		


	public:
		ModuleEnemy();
		~ModuleEnemy();

		bool Start() ;
		UpdateResult Update() ;
		UpdateResult PostUpdate() ;

		void OnCollision(Collider* c1, Collider* c2) ;

		iPoint position;
		int speed = 1;

		SDL_Texture* texture = nullptr;

		Animation* currentAnimation = nullptr;

		Animation idleAnim;
		Animation forwardAnim;
		Animation backwardAnim;

};

