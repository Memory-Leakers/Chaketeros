#ifndef _POWERUPH
#define _POWERUPH

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"

class PowerUp
{
public:
    PowerUp(iPoint position, SDL_Texture* tex);

    ~PowerUp();

    void PostUpdate();

private:
    Collider* collision = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect* renderRect = nullptr;
    bool destructible = true;

public:
    iPoint position;
};
#endif
