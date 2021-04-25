#include "PowerUp.h"

PowerUp::PowerUp(iPoint position, SDL_Texture* tex) {

    this->position.x = position.x;
    this->position.y = position.y;
    App->collisions->AddCollider({ position.x , position.y, 16, 16 }, Type::DESTRUCTABLE_WALL, App->scene);
}

PowerUp::~PowerUp() {

}

void PowerUp::PostUpdate()
{
    App->render->DrawTexture(texture, position, renderRect);
}

void PowerUp::Die() {
    App->particle->AddParticle(*powerUpDestroyed, position, Type::NONE);
	
}

void PowerUp::OnCollision(Collider* c1,Collider* c2) {
	
	for (int i = 0; i < MAX_POWERUPS; ++i)
	{
		
		
		if ( Powers[i] == nullptr && Powers[i]->col == c1)
		{
			delete Powers[i];
			Powers[i] = nullptr;
			break;
		}
	}
}