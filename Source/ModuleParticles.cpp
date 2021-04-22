#include "ModuleParticles.h"


ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");

	explosionTexture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");

	//// ExplosionCenter particle
	explosionCenter.anim.PushBack({ 21, 2, 16, 16 });
	explosionCenter.anim.PushBack({ 21, 21, 16, 16 });
	explosionCenter.anim.PushBack({ 21, 40, 16, 16 });
	explosionCenter.anim.loop = false;
	explosionCenter.anim.speed = 0.01f;
	explosionCenter.lifetime = 500;
	explosionCenter.anim.hasIdle = false;
	explosionCenter.isAlive = true;

	//// ExplosionMiddle particle
	explosionMiddle.anim.PushBack({ 42, 2, 16, 16 });
	explosionMiddle.anim.PushBack({ 42, 21, 16, 16 });
	explosionMiddle.anim.PushBack({ 42, 40, 16, 16 });
	explosionMiddle.anim.loop = false;
	explosionMiddle.anim.speed = 0.01f;
	explosionMiddle.lifetime = 500;
	explosionMiddle.anim.hasIdle = false;
	explosionMiddle.isAlive = true;

	//// ExplosionEnd particle
	explosionEnd.anim.PushBack({ 62, 2, 16, 16 });
	explosionEnd.anim.PushBack({ 62, 21, 16, 16 });
	explosionEnd.anim.PushBack({ 62, 40, 16, 16 });
	explosionEnd.anim.loop = false;
	explosionEnd.anim.speed = 0.01f;
	explosionEnd.lifetime = 500;
	explosionEnd.anim.hasIdle = false;
	explosionEnd.isAlive = true;

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::CleanUpScene()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->col == c1)
		{
			// L6: TODO 6: Every time a particle hits a wall it triggers an explosion particle

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

UpdateResult ModuleParticles::PreUpdate()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle == nullptr)	continue;

		if(particle->anim.HasFinished())
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->DrawTexture(explosionTexture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, ::Type Type, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			// Adding the particle's 
			if (Type != Type::NONE)
			{
				p->col = App->collisions->AddCollider(p->anim.GetCurrentFrame(), Type, this);
			}
				
			particles[i] = p;
			break;
		}
	}
}

void ModuleParticles::AddParticle(const Particle& particle, iPoint pos, ::Type Type, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = pos.x;					// so when frameCount reaches 0 the particle will be activated
			p->position.y = pos.y;

			// Adding the particle's 
			if (Type != Type::NONE)
			{
				p->col = App->collisions->AddCollider(p->anim.GetCurrentFrame(), Type, this);
			}

			particles[i] = p;
			break;
		}
	}
}