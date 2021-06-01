#include "Application.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	// = nullptr for testing
	modules[0] = window = new ModuleWindow();
	modules[1] = input = new ModuleInput();
	modules[2] = textures = new ModuleTextures();
	modules[3] = particle = new ModuleParticles();
	modules[4] = audio = new ModuleAudio();
	modules[5] = scene = new ModuleScene();
	modules[6] = enemy = new ModuleEnemyPool();
	modules[7] = collisions = new ModuleCollisions();

	modules[8] = render = new ModuleRender();    //RENDER HAS TO BE ALWAYS THE LAST ONE ON THE modules ARRAY!!!!!!!!!!!!!!!!!!!!!!!!

	isPaused = false;
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		if(modules[i]!=nullptr)
		{
			// WARNING: When deleting a pointer, set it to nullptr afterwards
			// It allows us for null check in other parts of the code
			delete modules[i];
			modules[i] = nullptr;
		}
	}
}

bool Application::Init()
{
	bool ret = true;
	for (int i = 0; (i < NUM_MODULES) && ret; ++i)
	{
		if (modules[i] != nullptr)
		{
			ret = modules[i]->Init();
		}		
	}

	// We will consider that all modules are always active
	for (int i = 0; (i < NUM_MODULES) && ret; ++i)
	{
		if (modules[i] != nullptr)
		{
			ret = modules[i]->Start();
		}
	}
	return ret;
}

UpdateResult Application::Update()
{
	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	//TODO: (Opcional) Añadir sprite de Juego Pausado

	if (isPaused) 
	{ 
		modules[1]->PreUpdate();
		modules[1]->Update();
		modules[1]->PostUpdate(); 
		return ret; 
	}

	globalTime.Update();

	if (globalTime.getDeltaTime() >= 1.0f / FPS)
	{
		for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		{
			if (modules[i] != nullptr)
			{
				ret = modules[i]->PreUpdate();
			}
		}

		for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		{
			if (modules[i] != nullptr)
			{
				ret = modules[i]->Update();
			}
		}

		for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		{
			if (modules[i] != nullptr)
			{
				ret = modules[i]->PostUpdate();
			}
		}

		globalTime.Reset();
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; (i >= 0) && ret; --i)
	{
		if (modules[i] != nullptr)
		{
			ret = modules[i]->CleanUp();		
		}
	}

	return ret;
}
