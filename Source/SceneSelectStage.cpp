#include "SceneSelectStage.h"

#include <iostream>
using namespace std;

SceneSelectStage::SceneSelectStage()
{
}

SceneSelectStage::~SceneSelectStage()
{
}

bool SceneSelectStage::Start()
{
	cout << "Start Select Stage" << endl;
	return true;
}

bool SceneSelectStage::Update()
{
	cout << "Update Select Stage" << endl;
	return true;
}

bool SceneSelectStage::PostUpdate()
{
	cout << "PostUpdate Select Stage" << endl;
	return true;
}

bool SceneSelectStage::CleanUp(bool finalCleanUp)
{
	cout << "CleanUp Select Stage" << endl;
	return true;
}
