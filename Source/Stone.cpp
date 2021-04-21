#include "Stone.h"

Stone::Stone()
{
	SetTexture("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	SetRect({ 0,0,1,1 });

	Obstacle::Obstacle(this->getRect(), false, new Collider(this->getRect(), Type::WALL, App->scene), texture);

	idle.PushBack({ 8,6,16,21});
}

Stone::Stone(iPoint pos, SDL_Texture* tex) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::WALL, App->scene), tex)
{
	// Init para animacion
	idle.PushBack({ 8,6,16,21 });

	currentAnim = &idle;
}

void Stone::PostUpdate()
{
	App->render->DrawTexture(texture, this->getPosition(), &currentAnim->GetCurrentFrame());
}
