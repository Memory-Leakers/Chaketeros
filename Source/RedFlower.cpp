#include "RedFlower.h"


RedFlower::RedFlower()
{
	LOG("Constructor RedFlower");
}

RedFlower::RedFlower(iPoint pos, SDL_Texture* tex,Particle* dieParticle, Tile* tile) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	this->dieParticle = dieParticle;
	currentTileMap = tile;
	renderRect = { 110,110,16,16 };
}

void RedFlower::PostUpdate()
{
	if(!pendingToDelete)
	{	
		App->render->DrawTexture(texture, getPosition(), &renderRect);
	}
}

void RedFlower::Die() 
{
	int tileX, tileY;
	tileX = currentTileMap->getTilePos(getPosition()).x;
	tileY = currentTileMap->getTilePos(getPosition()).y;
	currentTileMap->Level1TileMap[tileY - 1][tileX] = 0;

	App->particle->AddParticle(*dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;	
}

void RedFlower::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
	}
}
