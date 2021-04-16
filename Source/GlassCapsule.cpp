#include "GlassCapsule.h"

GlassCapsule::GlassCapsule()
{
    //x and y position;
    SetRect({ 103,64,50,52 });
    texture = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/Fragments_with_machine");
    this->SetType(Type::WALL);
    this->SetDestructible(false);

    CurrentAnimation = &idleAnim;

    idleAnim.PushBack({ 46,114,48,62 });
    idleAnim.PushBack({ 102,112,48,63 });
    idleAnim.PushBack({ 157,112,48,64 });
    idleAnim.loop = true;

    withoutglassAnim.PushBack({ 45,191,48,49 });
    withoutglassAnim.PushBack({ 101,189,48,51 });
    withoutglassAnim.PushBack({ 156,186,48,54 });
    withoutglassAnim.loop = true;
}