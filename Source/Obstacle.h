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
	SDL_Rect r; // cuadrado de textura

protected:
	bool getDestructible();
	bool getTrigger();

public:
	SDL_Texture* texture = nullptr;

	// Animacion actual del obstaculo (NO TODO LOS OBSTACULOS TIENEN ANIMACION)
	//Animation* currentAnim = nullptr;
	
public:
//methods
	Obstacle();
	//Constructor
	Obstacle(SDL_Rect r, bool destructible, Collider* collider,SDL_Texture* texture, bool trigger = false);
	//Copy constructor
	Obstacle(const Obstacle& Obs);
	//Destructor
	~Obstacle();
	// Actualizar la posicion de la colision para que encaje con la posicion de la textura +
	virtual void OnCollision(Collider* col);

	virtual void Update();

	virtual void PostUpdate();

	virtual void Die();

	virtual void CleanUp();

	void ColUpdate();
protected:
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

	
	/// <summary>
	/// ejecuta si ha chocado con algo
	/// </summary>
	/// <param name="col">el cuerpo que ha choado</param>
public:
	
	Collider* getCollider();
	iPoint getPosition();
	SDL_Rect getRect();
	Type getType();
	

	

	bool pendingToDelete = false;

};
#endif // !__OBSTACLE_H__

