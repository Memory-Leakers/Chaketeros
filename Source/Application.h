#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleScene.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemyPool.h"
#include "ModuleDebug.h"

#include "Timer.h"

#define NUM_MODULES 10
#define FPS 60

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleEnemyPool;
class ModuleScene;
class ModuleRender;
class ModuleAudio;
class ModuleParticles;
class ModuleDebug;
class ModuleCollisions;

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

	ModuleEnemyPool* enemy = nullptr;

	ModuleScene* scene = nullptr;

	ModuleRender* render = nullptr;

	ModuleAudio* audio = nullptr;

	ModuleCollisions* collisions = nullptr;

	ModuleDebug* debug = nullptr;

	ModuleParticles* particle = nullptr;

	Timer globalTime;

	bool isPaused;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
