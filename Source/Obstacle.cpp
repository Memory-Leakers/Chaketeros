#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle()
{
<<<<<<< Updated upstream


}
Obstacle::Obstacle(SDL_Rect r, Type type, bool destructible, Collider* collider, SDL_Texture* texture, bool trigger) {
=======
}

Obstacle::Obstacle(SDL_Rect r, Collider::Type type, bool destructible, Collider* collider, SDL_Texture* texture, bool trigger) {
>>>>>>> Stashed changes
	this->r = r;
	this->type = type;
	this->destructible = destructible;
	this->collider = collider;
	this->texture = texture;
	this->trigger = trigger;
}

Obstacle::Obstacle(const Obstacle& Obs) {
	this->r = Obs.r; 
	this->type = Obs.type;
	this->collider = Obs.collider; 
	this->trigger = Obs.trigger;
	this->texture = Obs.texture;
	this->destructible = Obs.destructible;
}

Obstacle::~Obstacle() {


}

void Obstacle::SetDestructible(bool destructible)
{
	this->destructible = destructible;
};
void Obstacle::SetPos(iPoint position) {
	r.x = position.x;
	r.y = position.y;
};


void Obstacle::SetType(Type type)
{
	this->type = type;
}


void Obstacle::SetTexture(const char* path) {
	this->texture = App->textures->Load(path);
}

void Obstacle::SetCollider(Collider* collider)
{
	this->collider = collider;
}

<<<<<<< Updated upstream
void Obstacle::SetRect(SDL_Rect r) {
	this->r = r;
=======
void Obstacle::SetRect(SDL_Rect r)
{
	this->r = r;;
}

void Obstacle::SetDestructable(bool destructible)
{
	this->destructible = destructible;
>>>>>>> Stashed changes
}



bool Obstacle::getDestructible() {
	return destructible;
}

Collider* Obstacle::getCollider() {
	return collider;
}

iPoint Obstacle::getPosition()
{
	return { r.x, r.y };
}

SDL_Rect Obstacle::getRect()
{
	return this->r;
}

Type Obstacle::getType() {
	return type;
}

bool Obstacle::getTrigger() {
	return trigger;
}

void Obstacle::Update()
{
<<<<<<< Updated upstream
	cout << "Update Obs" << endl;
=======
	return;
>>>>>>> Stashed changes
}

void Obstacle::PostUpdate()
{
<<<<<<< Updated upstream
	cout << "PostUpdate Obs" << endl;
=======
	return;
>>>>>>> Stashed changes
}

void Obstacle::Die()
{
	LOG("Obstacle Destroyed");
}
