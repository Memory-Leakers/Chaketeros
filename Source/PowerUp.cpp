#include "PowerUp.h"

PowerUp::PowerUp(iPoint position, SDL_Texture* tex, SDL_Texture* dieTex, int powerType) {

    SDL_Rect powerRects[] = { { 2,2,16,16 }, { 2,2,16,16 }, { 20,20,16,16 }, { 20,2,16,16 }, { 2,20,16,16 } };


    renderRect = powerRects[powerType];

    texture = tex;

    powerUpDestroyed.InitParticle(500.0f, 0.3f, dieTex);
    powerUpDestroyed.anim.PushBack({ 3,2,26,27 });
    powerUpDestroyed.anim.PushBack({ 35,2,26,27 });
    powerUpDestroyed.anim.PushBack({ 67,2,26,27 });
    powerUpDestroyed.anim.PushBack({ 3,34,26,27 });
    powerUpDestroyed.anim.PushBack({ 35,34,26,27 });
    powerUpDestroyed.anim.PushBack({ 67,34,26,27 });
    powerUpDestroyed.anim.hasIdle = false;

    this->position.x = position.x;
    this->position.y = position.y;

    switch (powerType)
    {
    case 1:
        col = App->collisions->AddCollider({ position.x , position.y, 16, 16 }, Type::FIREPOWER, App->scene);
        break;
    case 2:
        col = App->collisions->AddCollider({ position.x , position.y, 16, 16 }, Type::BOMBPOWER, App->scene);
        break;
    case 3:
        col = App->collisions->AddCollider({ position.x , position.y, 16, 16 }, Type::INVINCIBLEPOWER, App->scene);
        break;
    }
    pickPowerUpSFX = App->audio->LoadSound("Assets/Audio/SFX/In_Game_Sounds/Objects_and_PowerUps_Sounds/G_PickPowerUpSound.wav");
}

PowerUp::~PowerUp()
{
}

void PowerUp::PostUpdate()
{
    App->render->AddTextureRenderQueue(texture, position, &renderRect, 1, position.y);
}

void PowerUp::Die()
{
    pendingToDelete = true;
    this->col->pendingToDelete = true;

    // Offset dieParticle
    iPoint tempPos = position;
    tempPos -= {5, 11};
    App->particle->AddParticle(powerUpDestroyed, tempPos, Type::NONE);
}

void PowerUp::OnCollision(Collider* col)
{
    if (col->type == Type::PLAYER)
    {
        App->audio->PlaySound(pickPowerUpSFX, 0);
        pendingToDelete = true;
        this->col->pendingToDelete = true;
    }
    else if(col->type == Type::EXPLOSION)
    {      
        Die();
    }
}
