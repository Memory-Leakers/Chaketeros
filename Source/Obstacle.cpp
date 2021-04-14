#include "Obstacle.h"
#include <iostream>
using namespace std;

Obstacle::Obstacle(SDL_Rect r,int flag, bool destructible, Collider* collider) {
	this->r = r;
	this->flag = flag;
	this->destructible = destructible;
	this->collider = collider;
}

Obstacle::Obstacle(const Obstacle& Obs) {
	this->r = Obs.r; this->flag = Obs.flag;
	this->collider = Obs.collider; this->trigger = Obs.trigger;
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

int Obstacle::getFlag() {
	return flag;
}

bool Obstacle::getDestructible() {
	return destructible;
}

bool Obstacle::getTrigger() {
	return trigger;
}