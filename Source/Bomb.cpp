#include "Bomb.h"

Bomb::Bomb()
{

}

Bomb::Bomb(iPoint pos) 
{
	this->texture = App->textures->Load("Assets/Images/Sprites/Player_Sprites/Bomb.png");
	
	Obstacle::Obstacle({ 0,0,16,16 }, true, new Collider(getRect(), Type::BOMB, App->obstacles),texture);

	defaultAnim.PushBack({ 1,1,16,16 });  //small
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
	defaultAnim.PushBack({ 1,39,16,16 }); //big
	defaultAnim.PushBack({ 1,21,16,16 }); //midle
}

void Bomb::PostUpdate()
{
	//App->render->DrawTexture()
}

void Bomb::Die()
{
	LOG("BombDie");
}
