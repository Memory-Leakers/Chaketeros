#pragma once

#include "ModuleEnemy.h"

#define moveTotDefault 2
#define dieAnimNum 6

class Saru : public ModuleEnemy {
	private:
		iPoint position;
		

		//GFX Relaeted
		SDL_Texture* texture = nullptr;
		Animation* currentAnimation = nullptr;
		Animation idleAnim;
		Animation upAnim;
		Animation downAnim;
		Animation rightAnim;
		Animation leftAnim;

		/*Die Animation*/
		Animation dieAnim[dieAnimNum];
		Timer deathTimer[dieAnimNum];
		Timer temporalTimer;
		int tempCount = 0;
		bool positioned = false;
		float stopTimer[dieAnimNum];
		int countDeath = -1;
		int tempY = 0;
		int tempX = 0;
		int f3C = 0;
		int f3CTop = 30;
		int f3CBottom = 0;
		Timer f3CTimer;
		bool f3CDir = true; //False down True Up

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


		iPoint tempPos;

		uint DeadSFX;

		bool injureAnim = false;


		Timer shotTimer;
		Timer updateTimer;

		/*Shoot specific*/
		Particle theShot;
		iPoint* bananacherPos = nullptr;
		bool shooting = false;
		

		void logic();
		void movement(int direction);
		void shot();
		void deathAnimSequence();
		void ProtectCountdown();
	public:

		Saru(iPoint spawnPos, iPoint* playerPos, iPoint* bananacherPos, Tile* tileMap);
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

