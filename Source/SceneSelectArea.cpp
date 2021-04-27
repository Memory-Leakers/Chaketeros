#include "SceneSelectArea.h"

#include <iostream>
using namespace std;

SceneSelectArea::SceneSelectArea()
{
}

SceneSelectArea::~SceneSelectArea()
{
}

bool SceneSelectArea::Start()
{
	cout << "Start Select Area" << endl;
	return true;
}

bool SceneSelectArea::Update()
{
	cout << "Update Select Area" << endl;
	return true;
}

bool SceneSelectArea::PostUpdate()
{
	cout << "PostUpdate Select Area" << endl;
	return true;
}

bool SceneSelectArea::CleanUp(bool finalCleanUp)
{
	delete text;
	cout << "CleanUp Select Area" << endl;
	return true;
}
