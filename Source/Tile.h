#ifndef _TILE_H_
#define _TILE_H_

#include "External/SDL/include/SDL_rect.h"
#include "Collider.h"
#include "Module.h"
#include "Point.h"
#include "Application.h"


class Tile
{
private:
	SDL_Rect r = { 0,0,16,16 };

	iPoint pivotPoint = { r.w / 2, r.h / 2 };

public:
	// 0 = EMPTY; 1 = INVISIBLE_WALL; 2 = STONE; 3 = RED FLOWER; 4 = NON EMPTY SPACE; 5 = YELLOW FLOWER	; 6 = CORE MECHA; 7 = GLASS CAPSULE BODY; 10 = GLASS CAPSULE

	int Level1TileMap[13][15]
	{
		{ 01,01,01,01,01,01,01,01,01,01,01,01,01,01,01 },
		{ 01,04,04,04,00,00,00,00,00,00,00,00,00,00,01 },
		{ 01,04,02,00,02,00,02,00,02,00,02,00,02,00,01 },
		{ 01,04,00,00,00,03,00,00,00,03,00,06,00,00,01 },
		{ 01,00,02,00,02,00,10,07,07,00,02,00,02,00,01 },
		{ 01,00,00,00,00,00,07,07,07,00,00,00,00,00,01 },
		{ 01,00,02,00,02,00,07,07,07,00,02,00,02,00,01 },
		{ 01,00,00,00,00,00,00,00,00,00,00,00,00,00,01 },
		{ 01,00,02,00,02,00,02,00,02,00,02,00,02,00,01 },
		{ 01,00,00,06,00,03,00,00,00,03,00,00,00,00,01 },
		{ 01,00,02,00,02,00,02,00,02,00,02,00,02,00,01 },
		{ 01,00,00,00,00,00,00,00,00,00,00,00,00,00,01 },
		{ 01,01,01,01,01,01,01,01,01,01,01,01,01,01,01 },
	};

	Tile();

	iPoint getWorldPos(iPoint pos);
	iPoint getWorldPos(int x, int y);

	iPoint getTilePos(iPoint pos);
	iPoint getTilePos(int x, int y);

	void setTile(iPoint tile,int num);
	void setTile(int tileX, int tileY, int num);

	void Reset();

};


#endif // !_TILE_H

