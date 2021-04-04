#include "Module.h"

bool Module::Init()
{
	return true;
}

update_status Module::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Module::Update()
{
	return update_status::UPDATE_CONTINUE;
}

update_status Module::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}