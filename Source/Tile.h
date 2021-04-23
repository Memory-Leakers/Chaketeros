#ifndef _TILE_H_
#define _TILE_H_

#include "External/SDL/include/SDL_rect.h"
#include "Collider.h"
#include "Module.h"
#include "Point.h"
#include "Application.h"


class Tile
{

public:

	SDL_Rect r = {0,0,16,16};

	iPoint pivotPoint = { r.w / 2, r.h / 2 };

	// 0 = EMPTY; 1 = INVISIBLE_WALL; 2 = STONE; 3 = RED FLOWER; 4 = NON EMPTY SPACE; 5 = YELLOW FLOWER	; 9 = GLASS CAPSULE

	int Level1TileMap[13][15]
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,4,4,4,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,4,2,0,2,0,2,0,2,0,2,0,2,0,1 },
		{ 1,4,0,0,0,3,0,0,0,3,0,0,0,0,1 },
		{ 1,0,2,0,2,0,9,4,4,0,2,0,2,0,1 },
		{ 1,0,0,0,0,0,4,4,4,0,0,0,0,0,1 },
		{ 1,0,2,0,2,0,4,4,4,0,2,0,2,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,2,0,2,0,2,0,2,0,2,0,2,0,1 },
		{ 1,0,0,0,0,3,0,0,0,3,0,0,0,0,1 },
		{ 1,0,2,0,2,0,2,0,2,0,2,0,2,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	};

	Tile();

	iPoint getWorldPos(iPoint pos);

	iPoint getTilePos(iPoint pos);

	void Reset();

};


#endif // !_TILE_H

