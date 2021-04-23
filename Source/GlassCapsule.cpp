#include "GlassCapsule.h"

GlassCapsule::GlassCapsule()
{
    LOG("Constructor GlassCapsule");
}

GlassCapsule::GlassCapsule(iPoint pos, SDL_Texture* tex) : Obstacle({ pos.x, pos.y, 16, 16 }, true, App->collisions->AddCollider({ pos.x, pos.y, 16, 16 }, Type::WALL, App->scene), tex)
{
    // Init para colision auxiliar
    int colPos[3][3] =
    {
        {0,1,1},
        {1,0,1},
        {1,0,1},
    };
    for (int i = 0, k = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (colPos[i][j] == 1)
            {
                auxCol[k++] = App->collisions->AddCollider({ pos.x + j * 16, pos.y + i * 16, 16, 16 }, Type::WALL, App->scene);
            }
        }
    }

	// Init para animacion
    idleAnim.hasIdle = false;
    idleAnim.PushBack({ 46,112,48,64 });
    idleAnim.PushBack({ 102,112,48,64 });
    idleAnim.PushBack({ 157,112,48,64 });
    idleAnim.PushBack({ 102,112,48,64 });
    idleAnim.speed = 0.05f;
    idleAnim.loop = true;

    withoutglassAnim.PushBack({ 45,191,48,49 });
    withoutglassAnim.PushBack({ 101,189,48,51 });
    withoutglassAnim.PushBack({ 156,186,48,54 });
    withoutglassAnim.loop = true;

    //withoutfragments.PushBack({});

    currentAnim = &idleAnim;
}

void GlassCapsule::Update() 
{
    currentAnim->Update();
}

void GlassCapsule::PostUpdate()
{  
    iPoint tempPos = getPosition();
    tempPos.y -= 16;
    App->render->DrawTexture(texture, tempPos, &currentAnim->GetCurrentFrame());

    //falta condicion
    /*CurrentAnimation = &withoutglassAnim
    rec = CurrentAnimation->GetCurrentFrame();
    App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &rec);
    */
}