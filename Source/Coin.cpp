#include "Coin.h"

Coin::~Coin()
{
}

Coin::Coin(iPoint position, SDL_Texture* texture) : Obstacle({ position.x, position.y, 16, 16 }, true, App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Type::NONE, App->scene), texture)
{
	idle.hasIdle = false;

	idle.PushBack({ 5,6,16,17 });
	idle.PushBack({ 26,6,16,17 });
	idle.PushBack({ 5,29,16,17 });
	idle.PushBack({ 26,28,16,17 });
	idle.speed = 0.08f;
	idle.loop = true;

	currentAnim = &idle;
}

void Coin::PostUpdate()
{
	currentAnim->Update();
	App->render->DrawTexture(texture, this->getPosition(), &currentAnim->GetCurrentFrame());
}

