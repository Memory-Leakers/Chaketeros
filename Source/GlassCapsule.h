#ifndef _GLASSCAPSULE_H_
#define _GLASSCAPSULE_H_

#include "Obstacle.h"


class GlassCapsule :public Obstacle {
public:

    GlassCapsule();
    GlassCapsule(iPoint pos, SDL_Texture* tex);
    ~GlassCapsule();

    //void OnCollision(Collider* c1,Collider* c2) override;
    iPoint position;
    //animation variables
    Animation idleAnim;
    Animation withoutglassAnim;
    Animation withoutfragments;

    bool isDead = false;
    
    int dieCount = 0;

    Collider* auxCol[6] = { nullptr };

public:

    void Update() override;
    void PostUpdate() override;
    void Die() override;
  

private:
    Animation* currentAnim = nullptr;
};
#endif // __GLASSCAPSULE_H_