#ifndef _POKAPOKA_H_
#define _POKAPOKA_H_

#include "ModuleEnemy.h"


class PokaPoka : public ModuleEnemy
{
	private:
		int moveRand = rand() % 4;
	
	protected:

		void die();

		void movement();
	
	public:

		PokaPoka(int x, int y);

		~PokaPoka();
		
		bool Start();
		UpdateResult Update();
		UpdateResult PostUpdate();

		void onCollision(Collider* otherCol);

		iPoint position;
		Collider* col = nullptr;
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

