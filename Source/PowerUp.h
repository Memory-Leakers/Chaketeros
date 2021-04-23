#ifndef _POWERUPH
#define _POWERUPH

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"

class PowerUp
{
public:
    PowerUp(iPoint position, SDL_Texture* tex, bool destruct);

    ~PowerUp();

    void PostUpdate();


private:
    Collider* collision;
    SDL_Texture* tex;
    bool destructible;

public:
    iPoint position;
    Animation idleAnim;

    Animation* currentAnimation;

};
#endif
