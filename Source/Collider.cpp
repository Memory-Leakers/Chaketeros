#include "Collider.h"
#include <iostream>
using namespace std;

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener): rect(rectangle), type(type), listener(listener)
{

}

Collider::~Collider()
{
	//delete listener;
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Collider::SetPos(iPoint pos)
{
	rect.x = pos.x;
	rect.y = pos.y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	// L6: TODO 1: Check if there is an overlap
	// between argument "r" and property "rect"
	if (rect.x < r.x && r.x < (rect.x + rect.w) ||
		rect.x < (r.x + r.w) && (r.x + r.w) < (rect.x + rect.w))
	{
		if (rect.y < r.y && r.y < (rect.y + rect.h) || 
			(rect.y < (r.y + r.h) && (r.y + r.h) < (rect.y + rect.h)))
		{
			return true;
		}
	}
	
	return false;
}