#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Module.h"

#include "ModuleDummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

#include "External/SDL/include/SDL.h"

// L2: TODO 0: Change the 'NUM_MODULES' value
#define NUM_MODULES 3

class ModuleDummy;
class ModuleWindow;
class ModuleRender;

class Application
{
public:

	// Constructor. Creates all necessary modules for the application
	Application();

	// Destructor. Removes all module objects
	~Application();

	// Initializes all modules
	bool Init();

	// Updates all modules (PreUpdate, Update and PostUpdate)
	UpdateResult Update();

	// Releases all the application data
	bool CleanUp();

public:

	// Array to store the pointers for the different modules
	Module* modules[NUM_MODULES];

	ModuleDummy* dummy = nullptr;
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__