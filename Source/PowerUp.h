#ifndef _POWERUPH
#define _POWERUPH

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "Obstacle.h"
#include "Particle.h"

class PowerUp
{
private:

    Collider* col = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect renderRect;
    uint pickPowerUpSFX;
public:

    bool pendingToDelete = false;
    Particle powerUpDestroyed;
    iPoint position;

public:
    PowerUp(iPoint position, SDL_Texture* tex, SDL_Texture* dieTex);

    ~PowerUp();

    void PostUpdate();

    void Die();

    void OnCollision(Collider* col);

    Collider* getCollider() { return col; }
};

#endif
