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
    col->pendingToDelete = true;
}

void PowerUp::PostUpdate()
{
    App->render->DrawTexture(texture, position, &renderRect);
}


Collider* PowerUp::getCollider()
{
    return col;
}

void PowerUp::Die() 
{
    App->particle->AddParticle(*powerUpDestroyed, position, Type::NONE);
}

void PowerUp::OnCollision(Collider* col) 
{	
    if (col->type == Type::PLAYER)
    {
        pendingToDelete = true;
    }
    else if(col->type == Type::EXPLOSION)
    {
        pendingToDelete = true;
        Die();
    }
}