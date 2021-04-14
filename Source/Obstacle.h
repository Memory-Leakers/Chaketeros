#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Module.h"
#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"

class Obstacle{

private:
	int flag;
	bool trigger;
	bool destructible;
	Collider* collider = nullptr;
	SDL_Rect r;
public:
	SDL_Texture* texture;
	
public:
//methods
	//Constructor
	Obstacle(SDL_Rect r,int flag, bool destructible, Collider* collider,SDL_Texture* texture);
	//Copy constructor
	Obstacle(const Obstacle& Obs);
	//Destructor
	~Obstacle();

	void SetPos(int x, int y);
	void SetFlag(int flag);
	void SetTexture(const char* path);
	bool getDestructible();
	bool getTrigger();
	int getFlag();
};
#endif // !__OBSTACLE_H__

