#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Application.h"

struct SDL_Window;
struct SDL_Surface;

// L2: TODO 1: Create the declaration of ModuleWindow class
// It should inherit from module and override all necessary functions

class ModuleWindow :public Module {

private:

public:

	bool Init() override;
	bool CleanUp() override;

	SDL_Window* myWindow;
	SDL_Surface* mySurface;

};

#endif // __MODULEWINDOW_H__

