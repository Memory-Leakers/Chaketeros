#pragma once

#include "ModuleEntity.h"


class ModuleEnemy : public ModuleEntity{

	private:

	protected:
		ModuleEnemy();
		~ModuleEnemy();
		
		bool Start() override;
		UpdateResult Update() override;
		UpdateResult PostUpdate() override;

		void OnCollision(Collider* c1, Collider* c2) override;

		iPoint position;
		int speed = 1;

		SDL_Texture* texture = nullptr;

		Animation* currentAnimation = nullptr;

		Animation idleAnim;
		Animation forwardAnim;
		Animation backwardAnim;


	public:


};

