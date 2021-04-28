#include "Coin.h"

Coin::~Coin()
{
}

Coin::Coin(iPoint position, SDL_Texture* texture) : Obstacle({ position.x, position.y, 16, 16 }, true, App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Type::COIN, App->scene), texture)
{
	idle.hasIdle = false;

	idle.PushBack({ 5,6,16,16 });
	idle.PushBack({ 26,5,16,16 });
	idle.PushBack({ 5,28,16,16 });
	idle.PushBack({ 26,28,16,16 });
	idle.speed = 0.08f;
	idle.loop = true;

	currentAnim = &idle;
}

void Coin::Update()
{
	currentAnim->Update();
}

void Coin::PostUpdate()
{
	App->render->DrawTexture(texture, this->getPosition(), &currentAnim->GetCurrentFrame());
}

void Coin::OnCollision(Collider* c1)
{
	if (c1->type == Type::PLAYER)
	{
		App->audio->PlaySound(SFX::PICK_COIN_SFX, 0);

		App->scene->currentScene->score += 100;

		pendingToDelete = true;
		getCollider()->pendingToDelete = true;
	}
	if (c1->type == Type::EXPLOSION)
	{
		App->scene->currentScene->score += 100;

		pendingToDelete = true;
		getCollider()->pendingToDelete = true;
	}
}
