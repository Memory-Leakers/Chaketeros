#ifndef _POKAPOKA_H_
#define _POKAPOKA_H_

#include "ModuleEnemy.h"
#include "Timer.h"
class PokaPoka : public ModuleEnemy
{
	private:
		int moveRand = rand() % 4;
		int pC = 0;
		iPoint nPoint;
		Particle* dieParticle = nullptr;
		iPoint* playerPos = nullptr;
		void attack();
		Timer attackTimer;
		Timer moveTimer;
		int attacking = 3;
	protected:
		
		void die();

		void movement();
	
	public:
		
		PokaPoka(int x, int y, iPoint* playerPos, Tile* level1Tile);

		~PokaPoka();
		
		bool Start();

		UpdateResult Update();
		UpdateResult PostUpdate();

		void OnCollision(Collider* col);

		iPoint position;
		
		int speed = 1; //Movement only

		SDL_Texture* texture = nullptr;

		Animation* currentAnimation = nullptr;

		Animation idleAnim;

		Animation upAnim;
		Animation downAnim;
		Animation rightAnim;
		Animation leftAnim;

		Animation attackAnim;
};

#endif // !_POLAPOLA_H_

