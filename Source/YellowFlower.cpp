#include "YellowFlower.h"


YellowFlower::YellowFlower() 
{
	LOG("Constructor yellowFlower");
}

YellowFlower::YellowFlower(iPoint pos, SDL_Texture* tex,Tile* tile, int hasPowerUp) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->currentTileMap = tile;
	this->hasPowerUp = hasPowerUp;

	//Init Particle
	this->dieParticle.InitParticle(500.0f, 0.3f, tex);
	this->dieParticle.anim.PushBack({ 17,0,16,16 });
	this->dieParticle.anim.PushBack({ 33,0,16,16 });
	this->dieParticle.anim.PushBack({ 49,0,16,16 });
	this->dieParticle.anim.PushBack({ 65,0,16,16 });
	this->dieParticle.anim.PushBack({ 81,0,16,16 });
	this->dieParticle.anim.PushBack({ 97,0,16,16 });
	this->dieParticle.anim.PushBack({ 113,0,16,16 });

	renderRect = { 0,0,16,16 };
}

void YellowFlower::Die()
{
	//Create destroyed particle;
	App->particle->AddParticle(dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;

	//Set TileMap Tile to 0 when Flower gets destroyed
	int tileX, tileY;
	tileX = currentTileMap->getTilePos(getPosition()).x;
	tileY = (currentTileMap->getTilePos(getPosition()).y);

	if (hasPowerUp == 1)
	{
		currentTileMap->LevelsTileMaps[App->scene->currentLevel][tileY - 1][tileX] = 8;
	}
	else
	{
		currentTileMap->LevelsTileMaps[App->scene->currentLevel][tileY - 1][tileX] = 0;
	}
}

void YellowFlower::PostUpdate()
{
	if(!pendingToDelete)
	{
		//App->render->DrawTexture(texture, getPosition(), &renderRect);
		App->render->AddTextureRenderQueue(texture, getPosition(), &renderRect, 1, getPosition().y);
	}
}

void YellowFlower::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
	}
}

