#include "YellowFlower.h"

YellowFlower::YellowFlower() 
{
	LOG("Constructor yellowFlower");
}

YellowFlower::YellowFlower(iPoint pos, SDL_Texture* tex, Particle* dieParicle) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	this->dieParticle = dieParicle;

	renderRect = { 9,8,16,16 };
}

void YellowFlower::PostUpdate()
{
	if(!pendingToDelete)
	{
		App->render->DrawTexture(texture, getPosition(), &renderRect);
	}
}

void YellowFlower::Die()
{
	App->particle->AddParticle(*dieParticle, getPosition(), Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;
}

void YellowFlower::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
	}
}

