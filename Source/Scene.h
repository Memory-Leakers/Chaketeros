#ifndef _SCENE_H_
#define _SCENE_H_

#include "Collider.h"

class Scene
{
protected:

	int ID;

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

	int getID()
	{
		return ID;
	}

	virtual bool CleanUp(bool finalCleanUp = true);

	int lastID = 0;


};


#endif //_SCENE_H_
