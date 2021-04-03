#include "ModuleRender.h"

extern Application* App;

bool ModuleRender::Init()
{
	SDL_Window* window = App->window->myWindow;
	myRender = SDL_CreateRenderer(window, -1, 0);

	if (myRender == nullptr)
	{
		LOG("Error");
		return false;
	}
	return true;
}

bool ModuleRender::CleanUp()
{
	if (myRender != nullptr)
	{
		SDL_DestroyRenderer(myRender);
	}

	return true;
}

UpdateResult ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(myRender, 255, 0, 0, 255);
	SDL_RenderClear(myRender);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::PostUpdate()
{
	SDL_RenderPresent(myRender);

	return UpdateResult::UPDATE_CONTINUE;
}



