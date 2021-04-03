#include "Module.h"

bool Module::Init()
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

bool Module::CleanUp()
{
	return true;
}