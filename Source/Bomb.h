#ifndef __BOMB_H__
#define __BOMB_H__

#include "Obstacle.h"
#include "Animation.h"

class Bomb : public Obstacle
{
private:
	// Rango de explosion de bomba
	int explotionRange = 3;
	// Cuanta atras de la explosion
	float explotionTime = 3;
	// Tiempo cuando empieza a contar
	double startCountTime;
	// Ataque de la bomba
	int attack = 1;

	// Animacion actual de la bomba
	Animation* currentAnim = nullptr;

	// Animaciones de la bomba
	Animation defaultAnim;

	// Textura de bomba;
	SDL_Texture* texture = nullptr;

public:
	Bomb();
	Bomb(iPoint pos);
	~Bomb();

	void Update() override;
	void PostUpdate() override;
	void Die() override;

	bool die = false;
};

#endif // !__BOMB_H__
