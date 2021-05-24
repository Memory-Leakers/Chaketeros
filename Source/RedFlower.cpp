#include "RedFlower.h"


RedFlower::RedFlower()
{
	LOG("Constructor RedFlower");
}

RedFlower::RedFlower(iPoint pos, SDL_Texture* tex, Tile* tile) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	currentTileMap = tile;
	renderRect = { 110,110,16,16 };

	dieParticle.InitParticle(500.0f, 0.3f, tex);
	dieParticle.anim.PushBack({ 2,133,16,16 });
	dieParticle.anim.PushBack({ 19,133,16,16 });
	dieParticle.anim.PushBack({ 36,133,16,16 });
	dieParticle.anim.PushBack({ 52,133,16,16 });
	dieParticle.anim.PushBack({ 69,133,16,16 });
	dieParticle.anim.PushBack({ 86,133,16,16 });
}

void RedFlower::PostUpdate()
{
	if(!pendingToDelete)
	{	
		//App->render->DrawTexture(texture, getPosition(), &renderRect);
		App->render->AddTextureRenderQueue(texture, getPosition(), &renderRect, 1, getPosition().y);
	}
}

void RedFlower::Die() 
{
	int tileX, tileY;
	tileX = currentTileMap->getTilePos(getPosition()).x;
	tileY = currentTileMap->getTilePos(getPosition()).y;
	currentTileMap->LevelsTileMaps[App->scene->currentLevel][tileY - 1][tileX] = 0;

	App->particle->AddParticle(dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;	
}

void RedFlower::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		App->scene->playerSettings->playerScore += 100;

		Die();
	}
}
