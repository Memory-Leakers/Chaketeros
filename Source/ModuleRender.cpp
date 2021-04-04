#include "ModuleRender.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"


SDL_Texture* texture;

ModuleRender::ModuleRender() : Module()
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// TODO 9: load a texture "Assets/test.png" to test is everything works well
	texture = App->textures->Load("Assets/Images/Sprites/UI_Sprites/BigMoney.png");

	return true;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	// TODO 7: Clear the screen to black before starting every frame
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	// TODO 10: Blit our test texture to check functionality
	SDL_Rect testRect = { 0, 0, 1280, 720 };
	Blit(texture, 0, 0, &testRect);
	// TODO 8: Display the rendered content to the screen
	SDL_RenderPresent(renderer);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy the rendering context
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect{ x, y, 0, 0 };
	
	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		//Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}