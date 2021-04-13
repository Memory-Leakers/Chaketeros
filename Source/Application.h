#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

// L2: DONE 0: Change the 'NUM_MODULES' value
#define NUM_MODULES 7

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModulePlayer;
class ModuleScene;
class ModuleRender;
class ModuleAudio;

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

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;

	ModulePlayer* player = nullptr;
	ModuleScene* scene = nullptr;
	ModuleRender* render = nullptr;

	ModuleAudio* audio = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__