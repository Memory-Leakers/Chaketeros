#ifndef _POWERUPH
#define _POWERUPH

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "Obstacle.h"
#include "Particle.h"

class PowerUp
{
public:
    PowerUp(iPoint position, SDL_Texture* tex , Particle* dieParticle);

    ~PowerUp();

    void PostUpdate();

    Collider* getCollider();

    void Die();

    void OnCollision(Collider* col) ;

private:

    Collider* col = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect renderRect;
  
public:
    
    bool pendingToDelete = false;
    Particle* powerUpDestroyed = nullptr;
    iPoint position;
};

#endif
