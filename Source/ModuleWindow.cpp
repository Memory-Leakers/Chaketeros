#include "ModuleWindow.h"

// L2: TODO 2: Init the library and check for possible errors using SDL_GetError()
bool ModuleWindow::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// L2: TODO 3: Pick the width and height and experiment with different window flags.
	// Create the window and check for errors
	// Expose the SDL_window as a public variable to access it through the different application modules

	Uint32 flags = SDL_WINDOW_OPENGL;

	myWindow = SDL_CreateWindow(
		"My windows",					   // window title
		SDL_WINDOWPOS_CENTERED,            // initial x position
		SDL_WINDOWPOS_CENTERED,            // initial y position
		SCREEN_WIDTH,                      // width, in pixels
		SCREEN_HEIGHT,                     // height, in pixels
		flags					           // flags - see below
	);

	if (myWindow == NULL) 
	{
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	// L2: TODO 4: Create a screen surface and keep it as a public variable
	mySurface = SDL_GetWindowSurface(myWindow);

	return true;
}

bool ModuleWindow::CleanUp()
{
	SDL_Quit();

	return true;
}

		
// L2: TODO 5: Fill with code the CleanUp() method
// Remove all the data and uninitialize SDL

