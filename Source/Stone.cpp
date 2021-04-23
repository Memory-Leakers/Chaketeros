#include "Stone.h"

Stone::Stone()
{
	LOG("Constructor Stone");
}

Stone::Stone(iPoint pos, SDL_Texture* tex) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::WALL, App->scene), tex)
{
	// Init para animacion
	renderRect = { 8,6,16,21 };
}

void Stone::PostUpdate()
{
	App->render->DrawTexture(texture, this->getPosition(), &renderRect);
}
