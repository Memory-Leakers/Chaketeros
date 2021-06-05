#include "ModuleWindow.h"

#include "Application.h"
#include "Globals.h"

#include "External/SDL/include/SDL.h"

ModuleWindow::ModuleWindow() : Module()
{

}

ModuleWindow::~ModuleWindow()
{

}

bool ModuleWindow::Init()
{
	LOG("Init SDL window and surface");
	bool ret = true;
	
	// L2: DONE 2: Init the library and check for possible errors using SDL_GetError()
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not be initialized! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (WIN_FULLSCREEN == true) flags |= SDL_WINDOW_FULLSCREEN;
		if (WIN_BORDERLESS == true)	flags |= SDL_WINDOW_BORDERLESS;
		if (WIN_RESIZABLE == true) flags |= SDL_WINDOW_RESIZABLE;
		if (App->FullScreenDesktop == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE, flags);

		if (window == nullptr)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// L2: DONE 4: Create a screen surface and keep it as a public variable
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp()
{
	// L2: DONE 5: Fill with code the CleanUp() method
	// Remove all the data and uninitialize SDL

	LOG("Destroying SDL window and quitting all SDL systems");

	// Destroy window
	

		if (window != NULL) SDL_DestroyWindow(window);

		// Quit SDL subsystems
		SDL_Quit();
	

	return true;
}
