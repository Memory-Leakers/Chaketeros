#pragma once

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleAudio.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"


class ModuleEntity : public Module{
	private:
		
	protected:
		struct SDL_Texture;

		ModuleEntity();
		~ModuleEntity();

		bool Start() override;
		UpdateResult Update() override;
		UpdateResult PostUpdate() override;

		void OnCollision(Collider* c1, Collider* c2) override;

		iPoint position;
		Collider c;
		int speed = 1;
		SDL_Texture* texture = nullptr;
		Animation* currentAnimation = nullptr;

		Animation idleAnim;
		Animation forwardAnim;
		Animation backwardAnim;

	public:

};

