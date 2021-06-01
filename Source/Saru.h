#pragma once

#include "ModuleEnemy.h"

#define moveTotDefault 2

class Saru : public ModuleEnemy
{
	private:
		int vRange = 40;//Range of vision of Saru
		int speed = 4; //Movement only
		int moveRangeCount = 0;
		SDL_Rect* rectSaru;
		iPoint* playerPos = nullptr;
		iPoint nPoint;
		bool onMovement = false;
		int direction = 4;
		int pC = 0;
		int movementTot = 6;
		int protectCount = 0;

		Timer shotTimer;
		Timer updateTimer;

		void logic();
		void movement(int direction);
		void shot();
		void ProtectCountdown();
	public:

		iPoint position;

		SDL_Texture* texture = nullptr;

		Animation* currentAnimation = nullptr;

		Animation idleAnim;
		Animation upAnim;
		Animation downAnim;
		Animation rightAnim;
		Animation leftAnim;

		Saru(iPoint spawnPos, iPoint* playerPos, Tile* tileMap);
		~Saru();

		bool Start();

		UpdateResult PreUpdate() override;
		UpdateResult Update() override;
		UpdateResult PostUpdate() override;

		void OnCollision(Collider* col) override;

		void Die() override;

		/*GETTERS AND SETTERS*/
		void setVRange(int vRange) { //Setters used to change Saru behaviour when bananacher dies
			this->vRange = vRange;
		}
};

