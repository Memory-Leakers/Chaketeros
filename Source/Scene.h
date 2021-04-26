#ifndef _SCENE_H_
#define _SCENE_H_

#include "Collider.h"
#include "Text.h"


class Scene
{

public:
	// Constructor
	Scene();

	// Destructor
	~Scene();

	virtual bool Start();

	virtual bool PreUpdate();

	virtual bool Update();

	virtual bool PostUpdate();

	virtual void OnCollision(Collider* c1, Collider* c2);

	virtual void WillCollision(Collider* c1, Collider* c2);

	virtual bool CleanUp(bool finalCleanUp = true);

	int score;
};


#endif //_SCENE_H_
