#include "ModuleDummy.h"

bool ModuleDummy::Init()
{
	LOG("Dummy Init!\n");

	return true;
}

UpdateResult ModuleDummy::PreUpdate()
{
	LOG("Dummy PreUpdate!\n");

	if (_kbhit() && _getch() == 27)
		return UpdateResult::UPDATE_STOP;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleDummy::Update()
{
	LOG("Dummy Update!\n");

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleDummy::PostUpdate()
{
	LOG("Dummy PostUpdate!\n");

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleDummy::CleanUp()
{
	LOG("Dummy CleanUp!\n");

	return true;
}