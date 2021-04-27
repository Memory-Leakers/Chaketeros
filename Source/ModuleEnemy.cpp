#include "ModuleEnemy.h"



ModuleEnemy::ModuleEnemy() {

};

ModuleEnemy::~ModuleEnemy() {
	//Power-Up drop
	//powerUpDrop();
};

bool ModuleEnemy::Start() {
	return true;
};

UpdateResult ModuleEnemy::Update() {
	return UpdateResult::UPDATE_CONTINUE;
};
UpdateResult ModuleEnemy::PostUpdate() {
	return UpdateResult::UPDATE_CONTINUE;
};
void ModuleEnemy::OnCollision(Collider* otherCol) {};
