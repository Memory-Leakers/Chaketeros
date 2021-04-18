#include "Bomb.h"

#include <iostream>
using namespace std;

Bomb::Bomb()
{

}

Bomb::Bomb(iPoint pos) :Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::BOMB, App->obstacles), texture)
{
	// Inicializar Bomba;
	this->texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");

	Obstacle::Obstacle({ 0,0,16,16 }, true, new Collider(getRect(), Type::BOMB, App->obstacles), texture);
	//Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::BOMB, App->obstacles), texture)


	// Obtener la textura de bomba	

	defaultAnim.hasIdle = false;
	// Inicializar animacion prestablecida de la bomba
	defaultAnim.PushBack({ 1,1,16,16 });  //small
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,20,16,16 }); //midle
	defaultAnim.PushBack({ 1,39,16,16 }); //big
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,20,16,16 }); //midle
	defaultAnim.speed = 0.02f;
	//defaultAnim.hasIdle = false;
	defaultAnim.loop = true;

	// Assignar anamacion prestablecida a currentAnim
	currentAnim = &defaultAnim;

	// Init TimeCount
	startCountTime = SDL_GetPerformanceCounter();
}

void Bomb::Update()
{
	currentAnim->Update();
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
	//App->render->DrawTexture()
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	App->render->DrawTexture(texture, this->getPosition(), &rect);
}

void Bomb::Die()
{
	LOG("BombDie");
	die = true;
	// Explision Center
	App->particle->AddParticle(App->particle->explosionCenter, getPosition(), Type::EXPLOSION);

	for (int i = 1; i < explotionRange; i++)
	{
		iPoint dir[4] = {
		{ (i) * 16, 0 },
		{ 0, (i) * 16 },
		{ (i) * -16, 0 },
		{ 0, (i) * -16 }
		};

		for (int j = 0; j < 4; ++j)
		{
			// Explosion Middle
			App->particle->AddParticle(App->particle->explosionMiddle, (getPosition() + dir[j]), Type::EXPLOSION);

			// Explosopn End
			if (i == explotionRange - 1)
			{
				++i;
				App->particle->AddParticle(App->particle->explosionEnd, getPosition() + dir[j], Type::EXPLOSION);
				--i;
			}
		}
	}
}