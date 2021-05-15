#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Animation.h"
#include "Collider.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "Application.h"
#include "PowerUp.h"
#include "Tile.h"



#define defaultEnemySpeed 0.13f //Animation only

struct SDL_Texture;

class ModuleEnemy : public Module{

protected:
		bool isFlip = false;;

		int points = 0; //Score points

		int destroyedFx = 0;
		bool isDead = false;

		SDL_Rect bounds;

		Tile* level1Tile = nullptr;

		virtual void movement() {};

		

public:
	ModuleEnemy();
	ModuleEnemy(int x, int y);
	~ModuleEnemy();

	virtual bool Start();
	virtual UpdateResult PreUpdate();
	virtual UpdateResult Update();
	virtual UpdateResult PostUpdate();
	virtual void OnCollision(Collider* col);
	virtual void die() {};

	iPoint position;

	iPoint pivotPoint;

	Collider* col = nullptr;

	int speed = 1; //Movement only

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	bool pendingToDelete = false;

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
};

#endif
