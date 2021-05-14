#include "SceneLevel2.h"
SceneLevel2::SceneLevel2()
{

}

SceneLevel2::~SceneLevel2()
{
}

void SceneLevel2::CreateScene()
{
}

void SceneLevel2::CreateYellowFlowers()
{
}

void SceneLevel2::CreateCoins()
{
}

void SceneLevel2::InitAssets()
{
	texMap = App->textures->Load("Assets/Images/Sprites/Environment_Sprites/MapLevel2.png");
}


bool SceneLevel2::Start()
{
	InitAssets();
	return false;
}

bool SceneLevel2::PreUpdate()
{
	return false;
}

bool SceneLevel2::Update()
{
	return false;
}

bool SceneLevel2::PostUpdate()
{
	App->render->AddTextureRenderQueue(texMap, { 0, 16 }, nullptr, 0, 0);
	return false;
}

void SceneLevel2::OnCollision(Collider* c1, Collider* c2)
{
}

void SceneLevel2::WillCollision(Collider* c1, Collider* c2)
{
}

bool SceneLevel2::CleanUp(bool finalCleanUp)
{
	return false;
}


