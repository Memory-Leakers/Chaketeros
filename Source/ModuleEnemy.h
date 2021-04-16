#pragma once

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"


#define defaultEnemySpeed 0.1f //Animation only

struct SDL_Texture;

class ModuleEnemy : public Module{

	private:
		int points = 0; //Score points

		int destroyedFx = 0;

		void powerUpDrop() {

		};
		void move() {

		};
	protected:


	public:

		~ModuleEnemy();

		bool Start() ;
		UpdateResult Update() ;
		UpdateResult PostUpdate() ;

		void OnCollision(Collider* otherCol);

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

		/*-----GETTERS AND SETTERS-----*/
		int getPoints() {
			return points;
		}
		void setPoints(int points) {
			this->points = points;
		}
		int getDestroyedFx() {
			return destroyedFx;
		}
		void setDestroyedFx(int fxId) {
			this->destroyedFx = fxId;
		}
		const Collider* getCollider() const {
			return col;
		}

		ModuleEnemy(int x, int y) {
			position.x = x;
			position.y = y;
		};
};
