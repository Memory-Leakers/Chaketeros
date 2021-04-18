#include "Tile.h"


Tile::Tile()
{

}


iPoint Tile::getWorldPos(iPoint pos)
{
	iPoint ret = { 0,0 };

	ret.x += 8;	//Ajuste para que encajen las Tiles

	ret.x += pivotPoint.x;	//Ajuste para que se alinee con el Pivot Point
	ret.y += pivotPoint.y;

	ret.x += pos.x * 16;
	ret.y += pos.y * 16;

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
