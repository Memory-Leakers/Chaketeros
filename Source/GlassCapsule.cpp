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
    for (int i = 0, k = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
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

    withoutglassAnim.PushBack({ 46,186,48,54 });
    withoutglassAnim.PushBack({ 102,186,48,54 });
    withoutglassAnim.PushBack({ 157,186,48,54 });
    withoutglassAnim.loop = true;
    withoutglassAnim.speed = 0.03f;
    withoutglassAnim.hasIdle = false;
    
    withoutfragments.PushBack({102,47,48,54});

    currentAnim = &idleAnim;
}

void GlassCapsule::Update() 
{
    currentAnim->Update();
}

void GlassCapsule::PostUpdate()
{  
    iPoint tempPos = getPosition();;
    if (!isDead)
    {
        tempPos.y -= 16;
        //App->render->DrawTexture(texture, tempPos, &currentAnim->GetCurrentFrame());   
    }
    else 
    {
        tempPos.y -= 6;
       //App->render->DrawTexture(texture, tempPos, &currentAnim->GetCurrentFrame());
    }
    App->render->AddTextureRenderQueue(texture, tempPos, &currentAnim->GetCurrentFrame(), 1, getPosition().y);
}

void GlassCapsule::Die()
{
    dieCount++;
    if (dieCount == 1) 
    {
        isDead = true;
        currentAnim = &withoutglassAnim;
    }
    
    if (dieCount == 2) 
    {
        currentAnim = &withoutfragments;
    }
}

