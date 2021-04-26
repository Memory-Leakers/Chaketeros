#include "YellowFlower.h"


YellowFlower::YellowFlower() 
{
	LOG("Constructor yellowFlower");
}

YellowFlower::YellowFlower(iPoint pos, SDL_Texture* tex, Particle* dieParicle,Tile* tile, bool hasPowerUp) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->currentTileMap = tile;
	this->dieParticle = dieParicle;
	this->hasPowerUp = hasPowerUp;

	renderRect = { 0,0,16,16 };
}

void YellowFlower::Die()
{
	//Create destroyed particle;
	App->particle->AddParticle(*dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;

	//Set TileMap Tile to 0 when Flower gets destroyed
	int tileX, tileY;
	tileX = currentTileMap->getTilePos(getPosition()).x;
	tileY = (currentTileMap->getTilePos(getPosition()).y);

	if (hasPowerUp)
	{
		currentTileMap->Level1TileMap[tileY - 1][tileX] = 8;
	}
	else
	{
		currentTileMap->Level1TileMap[tileY - 1][tileX] = 0;
	}
}

void YellowFlower::PostUpdate()
{
	if(!pendingToDelete)
	{
		App->render->DrawTexture(texture, getPosition(), &renderRect);
	}
}

void YellowFlower::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
	}
}

