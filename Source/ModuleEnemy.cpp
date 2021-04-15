#include "ModuleEnemy.h"


ModuleEnemy::ModuleEnemy() {};
ModuleEnemy::~ModuleEnemy() {};

bool ModuleEnemy::Start() {
	return true;
};

UpdateResult ModuleEnemy::Update() {
	return UpdateResult::UPDATE_CONTINUE;
};
UpdateResult ModuleEnemy::PostUpdate() {
	return UpdateResult::UPDATE_CONTINUE;
};
void ModuleEnemy::OnCollision(Collider* c1, Collider* c2) {};