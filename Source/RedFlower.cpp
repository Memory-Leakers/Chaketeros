#include "RedFlower.h"


RedFlower::RedFlower()
{
	
	texture = App->textures->Load("Assets/Images/Sprites/Enemies_Sprites/Enemies.png");
	
	Obstacle::Obstacle({ 0,0,16,16 }, true, App->collisions->AddCollider(getRect(), Type::DESTRUCTABLE_WALL, App->obstacles), texture);

	idleAnim.PushBack({ 110,110,16,16 });
	CurrentAnimation = &idleAnim;
	//Red Flower Die Animation
	DieAnim.hasIdle = false;
	DieAnim.PushBack({ 2,133,16,16 });
	DieAnim.PushBack({ 19,133,16,16 });
	DieAnim.PushBack({ 36,133,16,16 });
	DieAnim.PushBack({ 52,133,16,16 });
	DieAnim.PushBack({ 69,133,16,16 });
	DieAnim.PushBack({ 86,133,16,16 });
	DieAnim.speed = 0.05f;
	DieAnim.loop = false;


}

void RedFlower::PostUpdate() {
	SDL_Rect rec = CurrentAnimation->GetCurrentFrame();
	App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &rec);


}

void RedFlower::DieUpdate() {
	CurrentAnimation = &DieAnim;
	
}