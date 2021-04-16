#ifndef __MODULE_ENEMYPOOL_H__
#define __MODULE_ENEMYPOOL_H__

#include "Module.h"
#include "Application.h"
#include "ModuleEnemy.h"

#define MAX_ENEMIES 25

enum class ENEMY_TYPE {
	NO_TYPE,
	POKAPOKA,
	FLOWER,

};
struct EnemySpawnpoint {
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	int x, y;
};

class ModuleEnemy;
struct SDL_Texture;

class ModuleEnemyPool : public Module {
	private:
		void SpawnEnemy(const EnemySpawnpoint& info);
		EnemySpawnpoint spawnQueue[MAX_ENEMIES];
		ModuleEnemy* enemies[MAX_ENEMIES];
		//SDL_Texture* texture = nullptr; //Enemy sprite sheet

		int enemyDestroyedFx = 0;
	public:
		ModuleEnemyPool();
		~ModuleEnemyPool();

		bool Start() override;

		UpdateResult Update() override;
		UpdateResult PostUpdate() override;

		bool CleanUp() override; //Destroys all active enemies left in the array
		void OnCollision(Collider* c1, Collider* c2) override;

		bool AddEnemy(ENEMY_TYPE type, int x, int y); //Add enemy to the pool
		void HandleEnemiesSpawn();
};

#endif // __MODULE_ENEMYPOOL_H__