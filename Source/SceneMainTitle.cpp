#include "SceneMainTitle.h"

#include <iostream>
using namespace std;

SceneMainTitle::SceneMainTitle()
{
}

SceneMainTitle::~SceneMainTitle()
{
}

bool SceneMainTitle::Start()
{
	cout << "Start Main Title" << endl;
	return true;
}

bool SceneMainTitle::Update()
{
	cout << "Update Main Title" << endl;
	return true;
}

bool SceneMainTitle::PostUpdate()
{
	cout << "PostUpdate Main Title" << endl;
	return true;
}

bool SceneMainTitle::CleanUp(bool finalCleanUp)
{
	delete text;
	cout << "CleanUp Main Title" << endl;
	return true;
}
