#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "External/SDL/include/SDL_Rect.h"

#include "Point.h"

class Module;

enum class Type
{
	NONE = -1,
	WALL,
	PLAYER,
	ENEMY,
	BOMB,
	EXPLOSION,
	DESTRUCTABLE_WALL,
	MAX
};

struct Collider
{
	// Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	~Collider();

	void SetPos(int x, int y);

	void SetPos(iPoint pos);

	iPoint getPos();

	bool Intersects(const SDL_Rect& r) const;

	// Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};

#endif // !__COLLIDER_H__

