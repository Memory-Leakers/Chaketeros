#include "Stone.h"

Stone::Stone()
{
	SetTexture("Assets/Images/Sprites/Environment_Sprites/Stone.png");
	SetRect({ 0,0,1,1 });

	Obstacle::Obstacle(this->getRect(), false, new Collider(this->getRect(), Type::WALL, App->obstacles), texture);

	idle.PushBack({ 8,6,16,21});

}

void Stone::PostUpdate()
{
	App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &(idle.GetCurrentFrame()));
}
