#ifndef __BOMB_H__
#define __BOMB_H__

#include "Obstacle.h"
#include "Animation.h"
#include "Particle.h"

class Obstacle;

class Bomb : public Obstacle
{
private:
	// Cuanta atras de la explosion
	float explotionTime = 3.5f;

	// Tiempo cuando empieza a contar
	double startCountTime;

	// Rango de explosion de bomba
	int explotionRange = 3;

	int attack = 1;

	uint explosionSFX, putBombSFX;

	// curernt Anim
	Animation* currentAnim = nullptr;

	// Bomb Anim
	Animation defaultAnim;

	Particle explosionCenter;

	Particle explosionMiddle;

	Particle explosionEnd;

	iPoint myTilePos;

	Player* player = nullptr;

	Tile* lv1Tile = nullptr;

public:
	Bomb();

	Bomb(Player* p, SDL_Texture* tex, Tile* tile);

	~Bomb();

 	void PostUpdate() override;

	void Update() override;

	void OnCollision(Collider* col) override;

	void Die() override;

	void CleanUp() override;
};

#endif // !__BOMB_H__
