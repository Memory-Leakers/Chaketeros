#include "YellowFlower.h"

YellowFlower::YellowFlower() 
{
	LOG("Constructor yellowFlower");
}

YellowFlower::YellowFlower(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie, Particle* dieParicle) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->texDie = texDie;

	this->dieParticle = dieParicle;

	renderRect = { 9,8,16,16 };
}

void YellowFlower::Die()
{
	//Create destroyed particle;
	App->particle->AddParticle(*dieParticle, (getPosition()), Type::NONE);
	pendingToDelete = true;
}

void YellowFlower::PostUpdate()
{
	if(!pendingToDelete)
	{
		App->render->DrawTexture(texture, getPosition(), &renderRect);
	}
}

