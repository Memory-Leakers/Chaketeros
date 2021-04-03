#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Application.h"

struct SDL_Renderer;

class ModuleRender:public Module
{
public:
	SDL_Renderer* myRender;

	bool Init() override;
	bool CleanUp() override;

	UpdateResult PreUpdate() override;

	UpdateResult PostUpdate() override;
};

#endif

