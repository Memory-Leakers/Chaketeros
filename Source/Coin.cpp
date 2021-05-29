#include "Coin.h"

Coin::~Coin()
{
}

Coin::Coin(iPoint position, SDL_Texture* texture) : Obstacle({ position.x, position.y, 16, 16 }, true, App->collisions->AddCollider({ position.x, position.y, 16, 16 }, Type::COIN, App->scene), texture)
{
	#pragma region Init idle anim
	idle.hasIdle = false;

	idle.PushBack({ 5,6,16,16 });
	idle.PushBack({ 26,5,16,16 });
	idle.PushBack({ 5,28,16,16 });
	idle.PushBack({ 26,28,16,16 });
	idle.speed = 0.08f;
	idle.loop = true;
	#pragma endregion

	pickCoinSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Extra_Points_Sounds/G_PickCoinSound.wav");

	currentAnim = &idle;
}

void Coin::Update()
{
	currentAnim->Update();
}

void Coin::PostUpdate()
{
	//App->render->DrawTexture(texture, this->getPosition(), &currentAnim->GetCurrentFrame());
	App->render->AddTextureRenderQueue(texture, getPosition(), &currentAnim->GetCurrentFrame(), 1, getPosition().y);
}

void Coin::OnCollision(Collider* c1)
{
	if (c1->type == Type::PLAYER)
	{
		App->audio->PlaySound(pickCoinSFX, 0);

		App->scene->playerSettings->playerScore += 500;

		pendingToDelete = true;
		getCollider()->pendingToDelete = true;
	}
	if (c1->type == Type::EXPLOSION)
	{
		App->scene->playerSettings->playerScore += 500;

		pendingToDelete = true;
		getCollider()->pendingToDelete = true;
	}
}
