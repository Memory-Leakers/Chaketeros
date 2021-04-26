#include "SceneGameOver.h"

#include <iostream>
using namespace std;


SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

bool SceneGameOver::Start()
{
	cout << "Start Game Over" << endl;

	cout << "Score: " << this->score << endl;

	return true;
}

bool SceneGameOver::Update()
{
	//cout << "Update Game Over" << endl;
	return true;
}

bool SceneGameOver::PostUpdate()
{
	//cout << "PostUpdate Game Over" << endl;
	return true;
}

bool SceneGameOver::CleanUp(bool finalCleanUp)
{
	cout << "CleanUp Game Over" << endl;
	return true;
}
