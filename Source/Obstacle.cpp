#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle(SDL_Rect r, Collider::Type type, bool destructible, Collider* collider, SDL_Texture* texture, bool trigger) {
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

void Obstacle::SetPos(iPoint position) {
	r.x = position.x;
	r.y = position.y;
};


void Obstacle::SetType(Collider::Type type)
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

Collider::Type Obstacle::getType() {
	return type;
}

bool Obstacle::getTrigger() {
	return trigger;
}

void Obstacle::Die()
{
	LOG("Obstacle Destroyed");
}
