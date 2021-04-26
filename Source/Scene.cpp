#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::Start()
{
	score = 0;
	return true;
}

bool Scene::PreUpdate()
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

void Scene::WillCollision(Collider* c1, Collider* c2)
{
}

bool Scene::CleanUp(bool finalCleanUp)
{
	return true;
}
