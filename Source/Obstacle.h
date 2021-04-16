#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"

class Obstacle{

private:
	Collider::Type type = Collider::Type::NONE;
	bool trigger;
	bool destructible;
	Collider* collider = nullptr;
	SDL_Rect r;
public:
	SDL_Texture* texture = nullptr;
	
public:
//methods
	//Constructor
	Obstacle(SDL_Rect r, Collider::Type type, bool destructible, Collider* collider,SDL_Texture* texture, bool trigger = false);
	//Copy constructor
	Obstacle(const Obstacle& Obs);
	//Destructor
	~Obstacle();

	void SetPos(iPoint position);
	void SetType(Collider::Type type);
	void SetTexture(const char* path);
	void SetCollider(Collider* collider);
	bool getDestructible();
	Collider* getCollider();
	iPoint getPosition();
	SDL_Rect getRect();
	Collider::Type getType();
	bool getTrigger();

	virtual void Die();

};
#endif // !__OBSTACLE_H__

