#include "ModuleTextures.h"

//#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	// TODO 5: Initialize all texture pointers to nullptr
	for (int i = 0; i < MAX_TEXTURES; i++) {
		textures[i] = nullptr;
	}
}

ModuleTextures::~ModuleTextures()
{}

bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	// Check if all flags were initialized correctly
	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	// TODO 6: Free all textures

	for (int i = 0; i < MAX_TEXTURES; i++) {
		SDL_DestroyTexture(textures[i]);
	}

	IMG_Quit();
	return true;
}

SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = nullptr;

	// TODO 2:	Load an SDL_Surface from a path (must be a png)
	//			and check for errors
	SDL_Surface* test;

	test = IMG_Load(path);

	if (test == NULL){ LOG("Error loading image: %s", SDL_GetError()) }


	// TODO 3:	Once your have the surface, create a texture from it (check for errors again)
	texture = SDL_CreateTextureFromSurface(App->render->renderer, test);

	if (texture == NULL){ LOG("Error loading texture: %s", SDL_GetError()) }


	// TODO 4:	Remember to free the surface at the end
	//			Add the texture to our own array so we can properly free all textures on application exit

	SDL_FreeSurface(test);

	for (int i = 0; i < MAX_TEXTURES; i++) { if (textures[i] == nullptr) { textures[i] = texture; break; } }


	return texture;
}
