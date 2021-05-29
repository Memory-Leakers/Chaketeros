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
	
		int points = 0; //Score points

		int destroyedFx = 0;

		int life = 1;

		bool isFlip = false;

		bool isDead = false;

		bool protect= false;

		SDL_Rect bounds;

		Tile* tileMap = nullptr;

protected:
		//virtual void movement();

		virtual void Die() {};

public:
	iPoint position;

	iPoint pivotPoint;

	Collider* col = nullptr;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	int speed = 1; //Movement only

	bool pendingToDelete = false;

public:

	ModuleEnemy();

	ModuleEnemy(int x, int y);

	~ModuleEnemy();

	virtual bool Start();

	virtual UpdateResult PreUpdate();

	virtual UpdateResult Update();

	virtual UpdateResult PostUpdate();

	virtual void OnCollision(Collider* col);

	/*-----GETTERS AND SETTERS-----*/
	int getPoints() { return points; }

	void setPoints(int points) { this->points = points; }

	int getDestroyedFx() { return destroyedFx; }

	void setDestroyedFx(int fxId) { this->destroyedFx = fxId; }

	const Collider* getCollider() const { return col; }
};

#endif
