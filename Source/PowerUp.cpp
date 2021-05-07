#include "PowerUp.h"

PowerUp::PowerUp(iPoint position, SDL_Texture* tex, Particle* dieParticle) {

    renderRect = { 2,2,16,16 };

    texture = tex;

    powerUpDestroyed = dieParticle;

    this->position.x = position.x;
    this->position.y = position.y;

    col = App->collisions->AddCollider({ position.x , position.y, 16, 16 }, Type::FIREPOWER, App->scene);
}

PowerUp::~PowerUp()
{
}

void PowerUp::PostUpdate()
{
    //App->render->DrawTexture(texture, position, &renderRect);
    App->render->AddTextureRenderQueue(texture, position, &renderRect, 1, position.y);
}

void PowerUp::Die()
{
    pendingToDelete = true;
    this->col->pendingToDelete = true;
    App->particle->AddParticle(*powerUpDestroyed, position, Type::NONE);
}

void PowerUp::OnCollision(Collider* col)
{
    if (col->type == Type::PLAYER)
    {
        App->audio->PlaySound(SFX::PICK_POWERUP_SFX, 0);
        pendingToDelete = true;
        this->col->pendingToDelete = true;
    }
    else if(col->type == Type::EXPLOSION)
    {      
        Die();
    }
}
