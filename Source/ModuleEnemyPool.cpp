#include "ModuleEnemyPool.h"


ModuleEnemyPool::ModuleEnemyPool() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		enemies[i] = nullptr;
	}
}

ModuleEnemyPool::~ModuleEnemyPool() {
	CleanUp();
}

bool ModuleEnemyPool::Start() {
	//texture = App->textures->Load("Assets/enemies.png");
	enemyDestroyedFx = App->audio->LoadSound("Assets/explosion.wav");

	return true;
}

UpdateResult ModuleEnemyPool::Update() {
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			enemies[i]->Update();
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleEnemyPool::PostUpdate() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			enemies[i]->PostUpdate();
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleEnemyPool::CleanUp() {
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemyPool::AddEnemy(ENEMY_TYPE type, int x, int y) {
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)  {
		if (spawnQueue[i].type == ENEMY_TYPE::NO_TYPE) {
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemyPool::HandleEnemiesSpawn() {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE) {
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}
}

void ModuleEnemyPool::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] == nullptr) {
			switch (info.type) {
				case ENEMY_TYPE::POKAPOKA:
					//enemies[i] = new ModulePokaPoka(info.x, info.y);
					break;
				case ENEMY_TYPE::FLOWER:
					//enemies[i] = new ModuleFlower(info.x, info.y);
					break;
			}
			//enemies[i]->texture = texture;
			enemies[i]->setDestroyedFx(enemyDestroyedFx);
			break;
		}
	}
}

void ModuleEnemyPool::OnCollision(Collider* c1, Collider* c2) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr && enemies[i]->getCollider() == c1) {
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}