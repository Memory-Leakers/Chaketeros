#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "External/SDL/include/SDL_Rect.h"

struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	//Constructor
	ModuleRender();

	//Destructor
	~ModuleRender();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Init() override;

	// Called at the beginning of the application loop
	// Clears the rendering context to a background color
	UpdateResult PreUpdate() override;

	// Called at the middle of the application loop
	// Handles camera movement
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	UpdateResult PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

	// Draws a texture to the screen
	// Param texture	- A valid SDL Texture, validation checks are not performed
	// Param x, y		- Position x,y in the screen (upper left axis)
	// Param section	- The portion of the texture we want to copy. nullptr for the entire texture
	// Param speed		- The amount of effect that is applied to the sprite depending on the camera
	bool DrawTexture(SDL_Texture* texture, int x, int y, SDL_Rect* section = nullptr, float speed = 1.0f);

	bool DrawRectangle(const SDL_Rect& rect, SDL_Color color, float speed = 1.0f);

public:
	// Rendering context used for any rendering action
	SDL_Renderer* renderer = nullptr;

	// A rectangle that represents the camera section
	// Sprites will be rendered to the screen depending on the camera position
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// The speed at which the camera will be moving
	int cameraSpeed = 3;
};

#endif //__MODULERENDER_H__
