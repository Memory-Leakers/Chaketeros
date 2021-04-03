#include "Application.h"

Application::Application()
{
	modules[0] = dummy = new ModuleDummy();

	// L2: TODO 1: Create the window module in application
	modules[1] = window = new ModuleWindow();

	modules[2] = render = new ModuleRender();
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		// Important! When deleting a pointer, set it to nullptr afterwards
		// It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	for (int i = 0; i < NUM_MODULES; ++i) modules[i]->Init();

	return true;
}

UpdateResult Application::Update()
{
	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; (i >= 0) && ret; --i) ret = modules[i]->CleanUp();

	return ret;
}
