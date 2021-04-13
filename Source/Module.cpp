#include "Module.h"

bool Module::Init()
{
	return true;
}

bool Module::Start()
{
	return true;
}

UpdateResult Module::PreUpdate()
{
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Module::Update()
{
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult Module::PostUpdate()
{
	return UpdateResult::UPDATE_CONTINUE;
}

void Module::OnCollision(Collider* c1, Collider* c2)
{

}

bool Module::CleanUp()
{
	return true;
}