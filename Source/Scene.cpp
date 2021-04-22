#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{
	return true;
}

bool Scene::Update()
{
	return true;
}

bool Scene::PostUpdate()
{
	return true;
}

void Scene::OnCollision(Collider* c1, Collider* c2)
{
}

bool Scene::CleanUp()
{
	return true;
}
