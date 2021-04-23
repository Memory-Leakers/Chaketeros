#include "PowerUp.h"

PowerUp::PowerUp(iPoint position, SDL_Texture* tex) {

	this->position.x = position.x;
	this->position.y = position.y;
}

void PowerUp::PostUpdate() 
{
	App->render->DrawTexture(texture, position, renderRect);
}