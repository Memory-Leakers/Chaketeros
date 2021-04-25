#ifndef _POWERUPH
#define _POWERUPH

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "Obstacle.h"
#define MAX_POWERUPS 5
class PowerUp
{
public:
    PowerUp(iPoint position, SDL_Texture* tex);

    ~PowerUp();

    void PostUpdate();

    void Die();

    void OnCollision(Collider* c1, Collider* c2) ;

private:
  
    PowerUp* Powers[MAX_POWERUPS];
    Collider* col = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect* renderRect = nullptr;
    bool destructible = true;

public:
    Particle* powerUpDestroyed = nullptr;
    iPoint position;
};
#endif
