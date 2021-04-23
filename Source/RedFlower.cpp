#include "RedFlower.h"


RedFlower::RedFlower()
{
	LOG("Constructor RedFlower");
}

RedFlower::RedFlower(iPoint pos, SDL_Texture* tex,Particle* dieParticle) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	this->dieParticle = dieParticle;
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
	App->particle->AddParticle(*dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
}