#include "ModuleObstacle.h"


#include "Application.h"

ModuleObstacle::ModuleObstacle() 
{

	for (int i = 0; i < MAX_OBSTACLES; i++) 
	{
		obstacles[i] = nullptr;
	}


}

ModuleObstacle::~ModuleObstacle() 
{}

bool ModuleObstacle::Start()
{
	LOG("Loading Obstacles");

	return true;
}


bool ModuleObstacle::CleanUp()
{

	for (int i = 0; i < MAX_OBSTACLES; i++) 
	{
		delete obstacles[i];
		obstacles[i] = nullptr;
	}

	return true;
}

void ModuleObstacle::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_OBSTACLES; ++i)
	{
		// Always destroy particles that collide
		if (obstacles[i] != nullptr && obstacles[i]->getCollider() == c1)
		{
			
			if (obstacles[i]->getType() == Collider::Type::DESTRUCTABLE_WALL && c2->type == Collider::Type::EXPLOSION) 
			{
				obstacles[i]->Die();
				delete obstacles[i];
				obstacles[i] = nullptr;
				break;
			}

		}
	}

}

void ModuleObstacle::AddObstacle(const Obstacle& obstacle, iPoint position, Collider::Type type)
{
	for (uint i = 0; i < MAX_OBSTACLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (obstacles[i] == nullptr)
		{
			Obstacle* p = new Obstacle(obstacle);

			p->SetPos(position); 						


			// Adding the particle's collider
			if (type != Collider::Type::NONE)
				p->SetCollider(App->collisions->AddCollider(p->getRect(), type, this));

			obstacles[i] = p;
			break;
		}
	}

}

