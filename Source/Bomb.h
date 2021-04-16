#ifndef __BOMB_H__
#define __BOMB_H__

#include "Obstacle.h"
#include "Animation.h"

class Bomb : public Obstacle
{
private:
	// Rango de explosion de bomba
	int explotionRange;
	// Cuanta atras de la explosion
	float explotionTime = 5;
	// Tiempo cuando empieza a contar
	double startCountTime;

	// Animaciones de la bomba
	Animation defaultAnim;

	// Textura de bomba;
	SDL_Texture* texture = nullptr;

public:
	Bomb();
	Bomb(iPoint pos);
	~Bomb();

	void PostUpdate() override;
	void Die() override;
};

#endif // !__BOMB_H__
