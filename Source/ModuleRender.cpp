#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include <algorithm>

#include "External/SDL/include/SDL_render.h"
#include "External/SDL/include/SDL_scancode.h"

// objects to render
vector<vector<RenderObject>> layers;
vector<RenderRect> rects;

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

	if (VSYNC == true) flags |= SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	//texter = new Text();

	if (renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// Fullscreen
	/*SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);*/

	// init layers size
	layers.resize(3);

	return ret;
}

// Called every draw update
UpdateResult ModuleRender::PreUpdate()
{
	// Set the color used for drawing operations
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	// Clear rendering target
	SDL_RenderClear(renderer);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::Update()
{
	#pragma region Debug key

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN)
	{
		debugCamera = !debugCamera;
		startCountTime = SDL_GetPerformanceCounter();
		if (!debugCamera) 
		{
			camera.y = 0;
			camera.x = 0;
		}
	}

	if (debugCamera) 
	{
		// Handle positive vertical movement
		if (App->input->keys[SDL_SCANCODE_UP] == KEY_REPEAT) camera.y -= cameraSpeed;

		// Handle negative vertical movement
		if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_REPEAT) camera.y += cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT) camera.x += cameraSpeed;

		if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_REPEAT) camera.x -= cameraSpeed;
	}

	#pragma endregion

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleRender::PostUpdate()
{
	for (int i = 0; i < layers.size(); i++)
	{
		SortRenderObjects(layers[i]);
	}

	// Draw layers
	for each (auto renderObj in layers[0])
	{
		SDL_RenderCopy(renderer, renderObj.texture, renderObj.section, &renderObj.renderRect);
	}
	for each (auto renderObj in layers[1])
	{
		if (renderObj.rotation == 0)
		{
			SDL_RenderCopy(renderer, renderObj.texture, renderObj.section, &renderObj.renderRect);
		}
		else
		{
			// Flips
			SDL_RenderCopyEx(renderer, renderObj.texture, renderObj.section, &renderObj.renderRect, renderObj.rotation, NULL, renderObj.flip);
		}
	}
	for each (auto renderObj in layers[2])
	{
		SDL_RenderCopy(renderer, renderObj.texture, renderObj.section, &renderObj.renderRect);
	}
	// Draw rects
	for each (auto renderRect in rects)
	{
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, renderRect.color.r, renderRect.color.g, renderRect.color.b, renderRect.color.a);
		SDL_RenderFillRect(renderer, &renderRect.rect);
	}

	// Update the screen
	SDL_RenderPresent(renderer);

	// Clear layers
	for (int i = 0; i < 3; i++)
	{
		layers[i].clear();
	}

	// Clear rects
	rects.clear();

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	// Destroy the rendering context
	if (renderer != nullptr) SDL_DestroyRenderer(renderer);

	return true;
}

void ModuleRender::AddTextureRenderQueue(SDL_Texture* texture, iPoint pos, SDL_Rect* section, int layer, float orderInlayer, bool isFlipH, float rotation, float scale, float speed)
{
	RenderObject renderObject;
	/*if (scale != SCREEN_SIZE) {
		scale /= 3;
	}*/
	renderObject.texture = texture;
	renderObject.rotation = rotation;
	renderObject.section = section;
	renderObject.orderInLayer = orderInlayer;

	if (layer == 2) speed = 0;	//If texture in UI layer, it moves alongside the camera. Therefor, speed = 0;

	renderObject.renderRect.x = (int)(-camera.x * speed) + pos.x * scale;
	renderObject.renderRect.y = (int)(-camera.y * speed) + pos.y * scale;

	if (section != nullptr)
	{
		renderObject.renderRect.w = section->w;
		renderObject.renderRect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &renderObject.renderRect.w, &renderObject.renderRect.h);
	}

	renderObject.renderRect.w *= scale;
	renderObject.renderRect.h *= scale;

	if (isFlipH)
	{
		renderObject.flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		renderObject.flip = SDL_FLIP_VERTICAL;
	}
	
	layers[layer].push_back(renderObject);
}

void ModuleRender::AddRectRenderQueue(const SDL_Rect& rect, SDL_Color color, float speed)
{
	RenderRect rec;

	rec.color = color;
	rec.rect.x = (int)(-camera.x * speed) + rect.x * SCREEN_SIZE;
	rec.rect.y = (int)(-camera.y * speed) + rect.y * SCREEN_SIZE;
	rec.rect.w = rect.w * SCREEN_SIZE;
	rec.rect.h = rect.h * SCREEN_SIZE;

	rects.push_back(rec);
}

void ModuleRender::SortRenderObjects(vector<RenderObject>& obj)
{
	//sort(obj.begin(), obj.end(), CompareRenderObj);

	int less = 0;
	int objSize = obj.size();

	for (int i = 0; i < objSize; ++i)
	{
		less = i;
		for (int j = i; j < objSize; ++j)
		{
			if (obj[j].orderInLayer < obj[less].orderInLayer)
			{
				swap(obj[j], obj[less]);
			}
		}
	}
}

void ModuleRender::CameraMove(iPoint pos)
{
	//	If the target is on the area where camera can follow (not off limits)
	if (pos.x >= SCREEN_WIDTH / 2 && pos.x <= LEVEL2_MAP_WIDTH - (SCREEN_WIDTH / 2))
	{
		//	Camera position = target position
		camera.x = pos.x - (SCREEN_WIDTH / 2);	
		camera.y = pos.y;
	}
}

void ModuleRender::ResetCamera()
{
	camera.x = 0;
	camera.y = 0;
}

#pragma region Obsolete

// Draw to screen
bool ModuleRender::DrawTexture(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;

	SDL_Rect rect = {
			(int)(-camera.x * speed) + x * SCREEN_SIZE,
			(int)(-camera.y * speed) + y * SCREEN_SIZE,
			0, 0 };
	
	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawTexture(SDL_Texture* texture, iPoint pos, SDL_Rect* section, float speed)
{
	bool ret = true;

	SDL_Rect rect = {
		(int)(-camera.x * speed) + pos.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + pos.y * SCREEN_SIZE,
		0, 0 };

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawTextureFreeScaled(SDL_Texture* texture, iPoint pos, float scale, SDL_Rect* section, float speed)
{
	bool ret = true;

	SDL_Rect rect = {
		(int)(-camera.x * speed) + pos.x * scale,
		(int)(-camera.y * speed) + pos.y * scale,
		0, 0 };

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= scale;
	rect.h *= scale;

	if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawRotateTexture(SDL_Texture* texture, iPoint pos, SDL_Rect* section, bool flipHor, float rotation, float speed)
{
	bool ret = true;

	SDL_Rect rect = {
		(int)(-camera.x * speed) + pos.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + pos.y * SCREEN_SIZE,
		0, 0 };

	if (section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		// Collect the texture size into rect.w and rect.h variables
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	SDL_RendererFlip flip;

	if (flipHor)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_VERTICAL;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, rotation, NULL, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawRectangle(const SDL_Rect& rect, SDL_Color color, float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect dstRect{
		(int)(-camera.x * speed) + rect.x * SCREEN_SIZE,
		(int)(-camera.y * speed) + rect.y * SCREEN_SIZE,
		rect.w * SCREEN_SIZE, rect.h * SCREEN_SIZE };

	if (SDL_RenderFillRect(renderer, &dstRect) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}


void ModuleRender::CameraMove(iPoint pos)
{
	if (pos.x >= SCREEN_WIDTH / 2 && pos.x <= LEVEL2_MAP_WIDTH - (SCREEN_WIDTH / 2))//	If the target is on the area where camera can follow (not off limits)
	{
		camera.x = pos.x - (SCREEN_WIDTH / 2);	//	Camera position = target position
		
		camera.y = pos.y;
		
	}
}
void ModuleRender::ResetCamera()
{
	camera.x = 0;
	camera.y = 0;
}

#pragma endregion
