#include "Bomb.h"

#include <iostream>
using namespace std;

Bomb::Bomb()
{
	LOG("Bomb constructor");
}

Bomb::Bomb(iPoint pos, SDL_Texture* tex, Particle* e1, Particle* e2, Particle* e3) :Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::BOMB, App->scene), tex)
{
	explosionCenter = *e1;
	explosionMiddle = *e2;
	explosionEnd = *e3;

	// Inicializar animacion prestablecida de la bomba
	defaultAnim.hasIdle = false;
	defaultAnim.speed = 0.02f;
	defaultAnim.loop = true;
	defaultAnim.PushBack({ 1,1,16,16 });  //small
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,39,16,16 }); //big
	defaultAnim.PushBack({ 1,21,16,16 }); //midle

	// Assignar anamacion prestablecida a currentAnim
	currentAnim = &defaultAnim;

	// Init TimeCount
	startCountTime = SDL_GetPerformanceCounter();
}

Bomb::~Bomb()
{
	// Liberar memoria de animacion
	if (currentAnim != nullptr)
	{
		delete currentAnim;
		currentAnim = nullptr;
	}
}

void Bomb::Update()
{
	// Actualizar la posicion de colision
	ColUpdate();

	// Acualizar frame de animacion
	currentAnim->Update();

	// TEST
	if (!die)
	{
		// Cuenta Atras para que la bomba se explota
		double currentCountTime = SDL_GetPerformanceCounter();
		double timeOffset = SDL_GetPerformanceFrequency();

		if (((currentCountTime - startCountTime) / timeOffset) >= explotionTime)
		{
			Die();
		}
	}
}

void Bomb::PostUpdate()
{
	App->render->DrawTexture(texture, getPosition(), &currentAnim->GetCurrentFrame());
}

void Bomb::Die()
{
	LOG("BombDie");
	die = true;
	// Centro de la explocion
	App->particle->AddParticle(explosionCenter, getPosition(), Type::EXPLOSION);

	for (int i = 1; i < explotionRange; i++)
	{
		// 4 Direcciones de explocion
		iPoint dir[4] = {
		{ (i) * 16, 0 },
		{ 0, (i) * 16 },
		{ (i) * -16, 0 },
		{ 0, (i) * -16 }
		};

		for (int j = 0; j < 4; ++j)
		{
			// Explosopn End
			if (i == explotionRange - 1)
			{		
				++i;
				App->particle->AddParticle(explosionEnd, getPosition() + dir[j], Type::EXPLOSION);
				--i;
			}
			else
			{
				// Explosion Middle
				App->particle->AddParticle(explosionMiddle, (getPosition() + dir[j]), Type::EXPLOSION);
			}
		}
	}
}
