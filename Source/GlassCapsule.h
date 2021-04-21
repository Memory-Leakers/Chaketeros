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

    Collider* auxCol[6] = { nullptr };

public:

    void Update() override;
    void PostUpdate() override;
};
#endif // __GLASSCAPSULE_H_