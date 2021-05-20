#pragma once

#include "ModuleEnemy.h"


class Saru : public ModuleEnemy
{
	private:
		int speed = 1; //Movement only
		int lives = 5;
		SDL_Rect* rectSaru;
		iPoint* playerPos = nullptr;

		void logic();

	public:

		iPoint position;

		SDL_Texture* texture = nullptr;

		Animation* currentAnimation = nullptr;

		Animation idleAnim;
		Animation upAnim;
		Animation downAnim;
		Animation rightAnim;
		Animation leftAnim;

		Saru(int x, int y, iPoint* playerPos, Tile* level1Tile);
		~Saru();

		bool Start();

		UpdateResult Update();
		UpdateResult PostUpdate();

		void OnCollision(Collider* col);

		void die() override;
};

