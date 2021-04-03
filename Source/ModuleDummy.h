#ifndef __MODULEDUMMY_H__
#define __MODULEDUMMY_H__

#include "Module.h"
#include <conio.h>

class ModuleDummy : public Module
{
public:

	bool Init();

	UpdateResult PreUpdate();

	UpdateResult Update();

	UpdateResult PostUpdate();

	bool CleanUp();
};

#endif // __MODULEDUMMY_H__