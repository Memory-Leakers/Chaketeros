#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Collider.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "Scene.h"

class Obstacle{
private:
	bool trigger;

	bool destructible;

	Collider* collider = nullptr;

	// cuadrado de textura
	SDL_Rect r; 

protected:
	string name = "Default";

	bool getDestructible();

	bool getTrigger();
	// Set Position of an obstacle
	void SetPos(iPoint position);
	// Set Type 
	void SetType(Type type);
	// Change the current texture of an obstacle
	void SetTexture(const char* path);
	// Set Collider
	void SetCollider(Collider* collider);

	void SetRect(SDL_Rect r);

	void SetDestructible(bool destructible);

public:
	SDL_Texture* texture = nullptr;

	int powerUp = 0;

	bool pendingToDelete = false;
	
public:
	//methods
	Obstacle();
	//Constructor
	Obstacle(SDL_Rect r, bool destructible, Collider* collider,SDL_Texture* texture, bool trigger = false);
	//Copy constructor
	Obstacle(const Obstacle& Obs);
	//Destructor
	~Obstacle();
	
	virtual void OnCollision(Collider* col);

	virtual void Update();

	virtual void PostUpdate();

	virtual void Die();

	virtual void CleanUp();

	// Actualizar la posicion de la colision para que encaje con la posicion de la textura +
	void ColUpdate();

	Collider* getCollider();

	iPoint getPosition();

	SDL_Rect getRect();

	Type getType();

	bool CompareName(string name);

};
#endif // !__OBSTACLE_H__

