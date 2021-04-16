#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"

struct Obstacle{

private:
	Type type = Type::NONE;
	bool trigger;
	bool destructible;
	Collider* collider = nullptr;
	SDL_Rect r;
public:
	SDL_Texture* texture = nullptr;
	
public:
//methods
	Obstacle();
	//Constructor
	Obstacle(SDL_Rect r, Type type, bool destructible, Collider* collider,SDL_Texture* texture, bool trigger = false);
	//Copy constructor
	Obstacle(const Obstacle& Obs);
	//Destructor
	~Obstacle();

	void SetPos(iPoint position);
	void SetType(Type type);
	void SetTexture(const char* path);
	void SetCollider(Collider* collider);
	void SetRect(SDL_Rect r);
	void SetDestructible(bool destructible);
	bool getDestructible();
	Collider* getCollider();
	iPoint getPosition();
	SDL_Rect getRect();
	Type getType();
	bool getTrigger();


	virtual void Update();
	virtual void PostUpdate();
	virtual void Die();

};
#endif // !__OBSTACLE_H__

