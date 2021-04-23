#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle()
{


}

Obstacle::Obstacle(SDL_Rect r, bool destructible, Collider* collider, SDL_Texture* texture, bool trigger)
{
	this->r = collider->rect;
	this->destructible = destructible;
	this->collider = collider;
	this->texture = texture;
	this->trigger = trigger;
}

Obstacle::Obstacle(const Obstacle& Obs) 
{
	this->r = Obs.collider->rect;
	this->collider = Obs.collider; 
	this->trigger = Obs.trigger;
	this->texture = Obs.texture;
	this->destructible = Obs.destructible;
}

Obstacle::~Obstacle()
{
	if(collider!=nullptr)
	{
		collider->pendingToDelete = true;
	}
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
	this->collider->type = type;
}


void Obstacle::SetTexture(const char* path) {
	//this->texture = App->textures->Load(path);
}

void Obstacle::SetCollider(Collider* collider)
{
	this->collider = collider;
}

void Obstacle::SetRect(SDL_Rect r) {
	this->r = r;
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
	return collider->type;
}

bool Obstacle::getTrigger() {
	return trigger;
}

void Obstacle::ColUpdate()
{
	collider->SetPos(getPosition());
}

void Obstacle::Update()
{
	//cout << "Update Obs" << endl;
}

void Obstacle::PostUpdate()
{
	//cout << "PostUpdate Obs" << endl;
}

void Obstacle::OnCollision(Collider* col)
{
	//cout << "Col" << endl;
}

void Obstacle::Die()
{
	LOG("Obstacle Destroyed");
}

void Obstacle::CleanUp()
{
	LOG("Obstacle Clean");
}
