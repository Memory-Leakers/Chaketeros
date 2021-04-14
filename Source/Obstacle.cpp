#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle(SDL_Rect r,int flag, bool destructible, Collider* collider, SDL_Texture* texture) {
	this->r = r;
	this->flag = flag;
	this->destructible = destructible;
	this->collider = collider;
	this->texture = texture;
}

Obstacle::Obstacle(const Obstacle& Obs) {
	this->r = Obs.r; 
	this->flag = Obs.flag;
	this->collider = Obs.collider; 
	this->trigger = Obs.trigger;
	this->texture = Obs.texture;
}

Obstacle::~Obstacle() {


}

void Obstacle::SetPos(int x, int y) {
	r.x = x;
	r.y = y;
};

void Obstacle::SetFlag(int flag) {
	this->flag = flag;
}

void Obstacle::SetTexture(const char* path) {
	this->texture = App->textures->Load(path);
}

int Obstacle::getFlag() {
	return flag;
}

bool Obstacle::getDestructible() {
	return destructible;
}

bool Obstacle::getTrigger() {
	return trigger;
}