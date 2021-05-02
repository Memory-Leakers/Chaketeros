#ifndef _GLASSCAPSULE_H_
#define _GLASSCAPSULE_H_

#include "Obstacle.h"


class GlassCapsule :public Obstacle {
public:
    //Constructors
    GlassCapsule();
    GlassCapsule(iPoint pos, SDL_Texture* tex);
    //Desconstructor
    ~GlassCapsule();
    
    void Update() override;
    void PostUpdate() override;
    void Die() override;
  

private:
    
    iPoint position;
    //animation variables
    Animation idleAnim;
    Animation* currentAnim = nullptr;
    Animation withoutglassAnim;
    Animation withoutfragments;
    //Collision variables
    Collider* auxCol[6] = { nullptr };
    bool isDead = false;

    int dieCount = 0;
};
#endif // __GLASSCAPSULE_H_