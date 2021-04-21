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
{
	
}

bool ModuleObstacle::Start()
{
	LOG("Loading Obstacles");

	return true;
}

UpdateResult ModuleObstacle::Update()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		if(obstacles[i]!=nullptr)
		{
			obstacles[i]->Update();
		}	
	}
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleObstacle::PostUpdate()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->PostUpdate();
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}


bool ModuleObstacle::CleanUp()
{

	for (int i = 0; i < MAX_OBSTACLES; i++) 
	{
		if(obstacles[i] != nullptr)
		{
			delete obstacles[i];
			obstacles[i] = nullptr;
		}		
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
			if (obstacles[i]->getType() == Type::DESTRUCTABLE_WALL && c2->type == Type::EXPLOSION) 
			{
				obstacles[i]->Die();
				delete obstacles[i];
				obstacles[i] = nullptr;
				break;
			}

		}
	}
}


void ModuleObstacle::AddObstacle(Obstacle& obstacle, iPoint position, Type type)
{
	for (uint i = 0; i < MAX_OBSTACLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (obstacles[i] == nullptr)
		{
			obstacle.SetPos(position); 						
			//obstacle.SetType(type);
			obstacles[i] = &obstacle;
			break;
		}
	}
}

