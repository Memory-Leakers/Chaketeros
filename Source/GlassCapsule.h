#ifndef _GLASSCAPSULE_H_
#define _GLASSCAPSULE_H_

#include "Obstacle.h"

class GlassCapsule :public Obstacle {
protected:

    GlassCapsule();

    ~GlassCapsule();

    //void OnCollision(Collider* c1,Collider* c2) override;
    iPoint position;
    //animation variables
    Animation idleAnim;
    Animation withoutglassAnim;
    Animation* CurrentAnimation;
};
#endif // __GLASSCAPSULE_H_