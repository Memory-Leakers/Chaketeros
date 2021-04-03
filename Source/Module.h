#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

class Module
{
public:
	//Called at the beginning of the application execution
	virtual bool Init();

	//Called at the beginning of each application loop
	virtual UpdateResult PreUpdate();

	//Called at the middle of each application loop
	virtual UpdateResult Update();

	//Called at the end of each application loop
	virtual UpdateResult PostUpdate();

	//Called at the end of the application
	virtual bool CleanUp();

};

#endif // __MODULE_H__