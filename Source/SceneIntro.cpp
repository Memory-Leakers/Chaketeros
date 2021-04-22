#include "SceneIntro.h"

#include <iostream>
using namespace std;


SceneIntro::SceneIntro()
{
}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::Start()
{
	cout << "Start Scene Intro" << endl;
	return true;
}

bool SceneIntro::Update()
{
	cout << "Update Scene Intro" << endl;
	return true;
}

bool SceneIntro::PostUpdate()
{
	cout << "PostUpdate Scene Intro" << endl;
	return true;
}

bool SceneIntro::CleanUp()
{
	cout << "CleanUp Scene Intro" << endl;
	return true;
}
