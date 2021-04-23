#include "PowerUp.h"



PowerUp::PowerUp(iPoint position, SDL_Texture* tex, bool destruct) {

	this->position.x = position.x;
	this->position.y = position.y;
	destruct = true;

	idleAnim.PushBack({ 2,2,16,16 });
}

void PowerUp::PostUpdate() {
	SDL_Rect* temprec = &currentAnimation->GetCurrentFrame();
	App->render->DrawTexture(tex, position, temprec);

}