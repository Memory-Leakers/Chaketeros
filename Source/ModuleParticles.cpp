#include "ModuleParticles.h"

Timer particleMoveTime;

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
	particleMoveTime.Update();

	if(particleMoveTime.getDeltaTime() > 0.025f)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle == nullptr)	continue;

			// Call particle Update. If it has reached its lifetime, destroy it
			if (particle->Update() == false)
			{
				delete particle;
				particles[i] = nullptr;
			}
		}
		particleMoveTime.Reset();
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
			if (particle->rotation != 0)
			{
				//App->render->DrawRotateTexture(particle->renderTex, particle->position, &(particle->anim.GetCurrentFrame()), particle->flipHor, particle->rotation);
				App->render->AddTextureRenderQueue(particle->renderTex, particle->position, &(particle->anim.GetCurrentFrame()), 1, particle->position.y, particle->flipHor, particle->rotation);
			}
			else
			{
				//App->render->DrawTexture(particle->renderTex, particle->position, &(particle->anim.GetCurrentFrame()));
				App->render->AddTextureRenderQueue(particle->renderTex, particle->position, &(particle->anim.GetCurrentFrame()), 1, particle->position.y);
			}
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

void ModuleParticles::AddParticle(const Particle& particle, iPoint pos, ::Type Type, bool flipHor, float rotation, uint delay)
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
			p->flipHor = flipHor;
			p->rotation = rotation;

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