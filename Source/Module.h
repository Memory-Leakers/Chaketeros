#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"
#include "Collider.h"

class Module
{
public:
	virtual ~Module() {}

	// Called at the beginning of the application execution
	virtual bool Init();

	// Called when the module is activated
	// By now we will consider all modules to be permanently active
	 virtual bool Start();

	// Called at the beginning of each application loop
	 virtual UpdateResult PreUpdate();

	// Called at the middle of each application loop
	 virtual UpdateResult Update();

	// Called at the end of each application loop
	 virtual UpdateResult PostUpdate();

	 // Called when two s are intersecting
	// and the module is registered as the listener
	 virtual void OnCollision(Collider* c1, Collider* c2);

	 virtual void WillCollision(Collider* c1, Collider* c2);

	// Called at the end of the application
	virtual bool CleanUp();
};

#endif // __MODULE_H__