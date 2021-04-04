#ifndef __MODULE_TEXTURES_H__
#define __MODULE_TEXTURES_H__

#include "Module.h"

#include "Application.h"
#include "ModuleRender.h"

#include "External/SDL/include/SDL.h"
#include "External/SDL_image/include/SDL_image.h"


#define MAX_TEXTURES 50

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	//Constructor
	ModuleTextures();
	//Destructor
	~ModuleTextures();

	// Called on application start.
	// Initializes the SDL_Image library
	bool Init() override;

	// Called on application exit.
	// Frees the memory from all stored textures
	// Uninitializes the SDL_Image library
	bool CleanUp() override;

	// Loads a new SDL_Texture from a file path
	// First creates an SDL_Surface, then converts it into SDL_Texture
	// Returns nullptr if the texture could not be created
	SDL_Texture* const Load(const char* path);

public:
	//Store all loaded textures so they can be freed on application exit
	SDL_Texture* textures[MAX_TEXTURES];

};

#endif // __ModuleTextures_H__