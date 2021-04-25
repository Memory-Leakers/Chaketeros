#include "CoreMecha.h"

CoreMecha::CoreMecha()
{
	LOG("Constructor yellowFlower");
}

CoreMecha::CoreMecha(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie, Particle* destroyed) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->texDie = texDie;
	this->dieParticle = *destroyed;

	renderRect = { 0, 0, 16, 26 };
}

void CoreMecha::Die()
{
	iPoint tempPos = getPosition();
	tempPos -= {5, 11};
	App->particle->AddParticle(dieParticle, tempPos, Type::NONE);
	pendingToDelete = true;
	getCollider()->pendingToDelete = true;
}

void CoreMecha::OnCollision(Collider* col)
{
	if (col->type == Type::EXPLOSION)
	{
		Die();
	}
}

void CoreMecha::PostUpdate()
{
	iPoint temp = this->getPosition();
	temp.y -= 10;

	App->render->DrawTexture(texture, temp, &renderRect);
}