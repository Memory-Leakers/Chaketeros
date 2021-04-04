#ifndef __MODULE_WINDOW_H__
#define __MODULE_WINDOW_H__

#include "Module.h"

//Try to figure out what this is used for
struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:
	//Constructor
	ModuleWindow();

	// Destructor
	~ModuleWindow();

	// Called on application start.
	// Initializes the SDL Library and creates a window.
	bool Init() override;

	// Called on application exit.
	// Destroys the window and uninitializes the SDL library
	bool CleanUp() override;

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The window's surface
	SDL_Surface* screenSurface = nullptr;
};

#endif // !__MODULE_WINDOW_H__

