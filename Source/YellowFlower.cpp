#include "YellowFlower.h"

YellowFlower::YellowFlower() 
{
	this->SetRect({ 0,0,1,1 });
	this->SetCollider(App->collisions->AddCollider(this->getRect(), Type::DESTRUCTABLE_WALL, App->scene));
	this->SetType(Type::DESTRUCTABLE_WALL);
	this->SetDestructible(true);
	this->SetTexture("Assets/Images/Sprites/Environment_Sprites/Yellow_Flower.png");
	texDie = App->textures->Load("Assets/Images/Sprites/PowerUps_Sprites/ItemDestroyedSheet.png");

	idle.PushBack({ 9,8,16,16 });

	currentAnim = &idle;

	die.PushBack({ 3,2,26,27 });
	die.PushBack({ 35,2,26,27 });
	die.PushBack({ 67,4,26,27 });
	die.PushBack({ 3,34,26,25 });
	die.PushBack({ 35,34,26,25 });
	die.PushBack({ 67,34,26,25 });
	die.speed = 0.5f;
	die.loop = true;
}

YellowFlower::YellowFlower(iPoint pos, SDL_Texture* tex, SDL_Texture* texDie) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene), tex)
{
	// Flow tienen sprites en diferentes sprite sheet, por eso necesita una textura aparte para guardar la animacion de morir
	this->texDie = texDie;

	idle.PushBack({ 9,8,16,16 });

	currentAnim = &idle;

	die.PushBack({ 3,2,26,27 });
	die.PushBack({ 35,2,26,27 });
	die.PushBack({ 67,4,26,27 });
	die.PushBack({ 3,34,26,25 });
	die.PushBack({ 35,34,26,25 });
	die.PushBack({ 67,34,26,25 });
	die.speed = 0.5f;
	die.loop = true;
}

void YellowFlower::Die()
{
	currentAnim = &die;
}

void YellowFlower::PostUpdate()
{
	//LOG("FlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\nFlowerUpdate\n");
	App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &(currentAnim->GetCurrentFrame()));
}

