#include "GlassCapsule.h"

GlassCapsule::GlassCapsule()
{
    //x and y position;
    texture = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine.png");
    /*SetRect({ 103,64,50,52 });
    
    this->SetType(Type::WALL);
    this->SetDestructible(false);
    */
    Obstacle::Obstacle({ 0,0,16,16 }, false, App->collisions->AddCollider(getRect(), Type::WALL, App->obstacles), texture);
    idleAnim.hasIdle = false;

    idleAnim.PushBack({ 46,112,48,64 });
    idleAnim.PushBack({ 102,112,48,64 });
    idleAnim.PushBack({ 157,112,48,64 });
    idleAnim.PushBack({ 102,112,48,64 });
    idleAnim.speed = 0.05f;
    idleAnim.loop = true;
    CurrentAnimation = &idleAnim;

    withoutglassAnim.PushBack({ 45,191,48,49 });
    withoutglassAnim.PushBack({ 101,189,48,51 });
    withoutglassAnim.PushBack({ 156,186,48,54 });
    withoutglassAnim.loop = true;

    withoutfragments.PushBack({});
}

void GlassCapsule::PostUpdate() {
    CurrentAnimation->Update();
    SDL_Rect rec = CurrentAnimation->GetCurrentFrame();
    App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &rec);

    //falta condicion
    /*CurrentAnimation = &withoutglassAnim
    rec = CurrentAnimation->GetCurrentFrame();
    App->render->DrawTexture(texture, this->getPosition().x, this->getPosition().y, &rec);
    */
}