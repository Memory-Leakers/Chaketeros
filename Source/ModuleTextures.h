#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Module.h"

#define MAX_TEXTURES 64

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	// Constructor
	ModuleTextures();

	// Destructor
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

	void CleanUpScene();

public:
	// An array of all the loaded textures
	// Allows us to keep track of all textures and free them on application exit
	SDL_Texture* textures[MAX_TEXTURES] = { nullptr };
};

#endif // __MODULETEXTURES_H__