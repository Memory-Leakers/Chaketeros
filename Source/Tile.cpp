#include "Tile.h"


Tile::Tile()
{

}


iPoint Tile::getWorldPos(iPoint pos)
{
	iPoint ret = { 0,0 };

	ret.x += 8;	//Ajuste para que encajen las Tiles

	/*ret.x += pivotPoint.x;	//Ajuste para que se alinee con el Pivot Point
	ret.y += pivotPoint.y;*/

	ret.x += pos.x * 16;
	ret.y += pos.y * 16;

	return ret;
}

iPoint Tile::getWorldPos(int x, int y)
{
	iPoint ret = { 0,0 };

	ret.x += 8;	//Ajuste para que encajen las Tiles

	ret.x += x * 16;
	ret.y += y * 16;

	return ret;
}

iPoint Tile::getTilePos(iPoint pos)	//EXAMPLE :31, 87	
{	
	pos.x -= 8;	// Restamos 8 mposiciones para compensar por el tamaño del mapa				//16

	pos.x -= pos.x % r.w;	//Calculamos el resto de cada eje	16
	pos.y -= pos.y % r.w;	// 80

	pos.x /= r.w;	//Encontrar el índice de Level1TileMap 1
	pos.y /= r.w;	// 5


	return {pos.x, pos.y};
}

iPoint Tile::getTilePos(int x, int y)
{
	x -= 8;	// Restamos 8 mposiciones para compensar por el tamaño del mapa				//16

	x -= (x % r.w);	//Calculamos el resto de cada eje	16
	y -= (y % r.w);	// 80

	x /= r.w;	//Encontrar el índice de Level1TileMap 1
	y /= r.w;	// 5

	return { x, y};
}

void Tile::Reset()
{
	for (int i = 0, k = 0; i < 13; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (Level1TileMap[i][j] == 5)
			{
				Level1TileMap[i][j] = 0;
			}
		}
	}
}
