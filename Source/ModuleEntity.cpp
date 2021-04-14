#include "ModuleEntity.h"


ModuleEntity::ModuleEntity() {};
ModuleEntity::~ModuleEntity() {};

bool ModuleEntity::Start() { };

UpdateResult ModuleEntity::Update() {};
UpdateResult ModuleEntity::PostUpdate() {};

void ModuleEntity::OnCollision(Collider* c1, Collider* c2) {};